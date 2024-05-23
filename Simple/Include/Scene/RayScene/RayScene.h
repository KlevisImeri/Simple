#pragma once

#include <vector>

#include "RayGpuProgam.h"
#include "Scene.h"
#include "vec3.h"
#include "Quadratic.h"

namespace simple {

class FullScreenTexturedQuad {
  //---------------------------
  unsigned int vao = 0;  // vertex array object id and texture id
 public:
  FullScreenTexturedQuad() {
    glGenVertexArrays(1, &vao);  // create 1 vertex array object
    glBindVertexArray(vao);      // make it active

    unsigned int vbo;       // vertex buffer objects
    glGenBuffers(1, &vbo);  // Generate 1 vertex buffer objects

    // vertex coordinates: vbo0 -> Attrib Array 0 -> vertexPosition of the vertex shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                                 // make it active, it is an array
    float vertexCoords[] = {-1, -1, 1, -1, 1, 1, -1, 1};                                // two triangles forming a quad
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), vertexCoords, GL_STATIC_DRAW);  // copy to that part of the memory which is not modified
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);  // stride and offset: it is tightly packed
  }

  void Draw() {
    glBindVertexArray(vao);               // make the vao and its vbos active playing the role of the data source
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  // draw two triangles forming a quad
  }
};

//---------------------------
class RayScene : public Scene {
  static inline RayGpuProgam rayGpuProgam;
  static inline const char *vertexSource = R"(
    #version 450
    precision highp float;

    uniform vec3 wLookAt, wRight, wUp;          // pos of eye

    layout(location = 0) in vec2 cCamWindowVertex;	// Attrib Array 0
    out vec3 p;

    void main() {
      gl_Position = vec4(cCamWindowVertex, 0, 1);
      p = wLookAt + wRight * cCamWindowVertex.x + wUp * cCamWindowVertex.y;
    }
  )";
  // fragment shader in GLSL
  static inline const char *fragmentSource = R"(
	#version 450
  precision highp float;

	struct Material {
		vec3 ka, kd, ks;
		float  shininess;
		vec3 F0;
		float n;	// index of refraction
		int type;
	};

	struct Light {
		vec3 direction;
		vec3 Le;
	};

  struct Quadratic {
    mat4 Q;
    int mat;
  };

	struct Hit {
		float t;
		vec3 position, normal;
		int mat;	// material index
	};

	struct Ray {
		vec3 start, dir;
		vec3 weight;
		bool outside;
		int depth;
	};

	const int nMaxObjects = 100, nMaxLights = 2;

	uniform vec3 wEye; 
	uniform int nLights;
	uniform Light lights[nMaxLights]; 
	uniform vec3 La;    
	uniform Material materials[4];  // diffuse, specular, ambient ref
	uniform int nObjects;
	uniform Quadratic objects[nMaxObjects];

	in  vec3 p;					// point on camera window corresponding to the pixel
	out vec4 fragmentColor;		// output that goes to the raster memory as told by glBindFragDataLocation

	Hit intersect(const Quadratic object, const Ray ray) {
		Hit hit;
		hit.t = -1;
    vec4 dir = vec4(ray.dir, 0.0);
    vec4 start = vec4(ray.start, 1.0);
    mat4 Q = object.Q;
		float a = dot(dir*Q, dir);
		float b = dot(start*Q, dir) * 2.0f;
		float c = dot(start*Q, start);
		float discr = b * b - 4.0f * a * c;
		if (discr < 0) return hit;
		float sqrt_discr = sqrt(discr);
		float t1 = (-b + sqrt_discr) / 2.0f / a;	// t1 >= t2 for sure
		float t2 = (-b - sqrt_discr) / 2.0f / a;
		if (t1 <= 0) return hit;
		hit.t = (t2 > 0) ? t2 : t1;
    hit.position = ray.start + ray.dir * hit.t;
    hit.normal = normalize(vec3(vec4(hit.position, 1.0) * Q));
		hit.mat = object.mat;
		return hit;
	}

	Hit firstIntersect(Ray ray) {
		Hit bestHit;
		bestHit.t = -1;
		for (int o = 0; o < nObjects; o++) {
			Hit hit = intersect(objects[o], ray); //  hit.t < 0 if no intersection
			if (hit.t > 0 && (bestHit.t < 0 || hit.t < bestHit.t))  bestHit = hit;
		}
		if (dot(ray.dir, bestHit.normal) > 0) bestHit.normal = bestHit.normal * (-1);
		return bestHit;
	}

	bool shadowIntersect(Ray ray) {	// for directional lights
		for (int o = 0; o < nObjects; o++) if (intersect(objects[o], ray).t > 0) return true; //  hit.t < 0 if no intersection
		return false;
	}

	vec3 Fresnel(vec3 F0, float cosTheta) { 
		return F0 + (vec3(1, 1, 1) - F0) * pow(cosTheta, 5);
	}

	const int maxdepth = 5;
	const int stackSize = 1 << maxdepth;

	struct Stack {
		Ray rays[stackSize];
		int sp;
	};

	const float epsilon = 0.0001f;

	vec3 trace(Ray ray) {
		vec3 outRadiance = vec3(0, 0, 0);

		Stack stack;
		stack.sp = 0;
		stack.rays[stack.sp++] = ray;	// push

//		while( stack.sp > 0 ) {
		for(int e = 0; e < stackSize; e++) {
	        if ( stack.sp == 0 ) return outRadiance;
			ray = stack.rays[--stack.sp];
			
//			while(ray.depth < maxdepth) {
			for(int d = 0; d < maxdepth; d++) {
				if (ray.depth >= maxdepth) break;

				Hit hit = firstIntersect(ray);
				if (hit.t <= 0) {
					outRadiance += ray.weight * La;
					break;
				}

				// rough surface, direct illumination
				if (materials[hit.mat].type == 0) {
					outRadiance += ray.weight * materials[hit.mat].ka * La;
					for(int l = 0; l < nLights; l++) {
						Ray shadowRay;
						shadowRay.start = hit.position + hit.normal * epsilon;
						shadowRay.dir = lights[l].direction;
						float cosTheta = dot(hit.normal, lights[l].direction);
						if (cosTheta > 0 && !shadowIntersect(shadowRay)) {
							outRadiance += ray.weight * lights[l].Le * materials[hit.mat].kd * cosTheta;
							vec3 halfway = normalize(-ray.dir + lights[l].direction);
							float cosDelta = dot(hit.normal, halfway);
							if (cosDelta > 0) outRadiance += ray.weight * lights[l].Le * materials[hit.mat].ks * pow(cosDelta, materials[hit.mat].shininess);
						}
					}
					break;
				}

				// refraction, postpone it
				if (materials[hit.mat].type == 2) {
					Ray refractRay;
					refractRay.start = hit.position - hit.normal * epsilon;
					refractRay.dir = refract(ray.dir, hit.normal, (ray.outside) ? materials[hit.mat].n : 1.0f / materials[hit.mat].n);
					refractRay.depth = ray.depth + 1;
					if (refractRay.depth < maxdepth && length(refractRay.dir) > 0) {
						refractRay.weight = ray.weight * (vec3(1, 1, 1) - Fresnel(materials[hit.mat].F0, dot(-ray.dir, hit.normal)));
						refractRay.outside = !ray.outside;
						stack.rays[stack.sp++] = refractRay;	// push
					}
				}

				// reflection
				ray.weight *= Fresnel(materials[hit.mat].F0, dot(-ray.dir, hit.normal));
				ray.start = hit.position + hit.normal * epsilon;
				ray.dir = reflect(ray.dir, hit.normal);
				ray.depth++;
			}
		}
		return outRadiance;
	}

	void main() {
		Ray ray;
		ray.start = wEye; 
		ray.dir = normalize(p - wEye);
		ray.weight = vec3(1, 1, 1);
		ray.outside = false;
		ray.depth = 0;
		fragmentColor = vec4(trace(ray), 1); 
	}
  )";

  FullScreenTexturedQuad fullScreenTexturedQuad;
  std::vector<Quadratic *> objects;
  std::vector<Light *> lights;
  vec3 La;
  Camera camera;
  std::vector<Material *> materials;

  float rnd() { return (float)rand() / RAND_MAX; }

 public:
  RayScene() {
    if (!rayGpuProgam.getId()) rayGpuProgam.create(vertexSource, fragmentSource, "fragmentColor");

    vec3 eye = vec3(0, 0, 2);
    vec3 vup = vec3(0, 1, 0);
    vec3 lookat = vec3(0, 0, 0);
    float fov = 45 * (float)M_PI / 180;
    camera.set(eye, lookat, vup, fov);

    La = vec3(0.5f, 0.4f, 0.4f);
    lights.push_back(new Light(vec3(1, 1, 1), vec3(3, 3, 3)));

    vec3 kd(0.3f, 0.2f, 0.1f), ks(10, 10, 10);
    materials.push_back(new RoughMaterial(kd, ks, 50));
    materials.push_back(new RoughMaterial(vec3(0.7f, 0.2f, 0.2f), vec3(0.02, 0.02, 0.02), 100));
    materials.push_back(new SmoothReflectorMaterial(vec3(0.95f, 0.85f, 0.75f)));
    materials.push_back(new SmoothRefractorMaterial(vec3(0.1f, 0.15f, 0.2f), 1.2f));

    objects.push_back((new Quadratic(mat4(1,    0,    0,    0,
                                          0,    0,    0,  0.5,
                                          0,    0,    1,    0,
                                          0,    0.5,  0,    0), 2))->Scale(0.6,1,0.6)->Translate(0.0,0.3,0.0));



    objects.push_back((new Quadratic(mat4(1,    0,    0,    0,
                                          0,    1,    0,    0,
                                          0,    0,    1,    0,
                                          0,    0,    0, -0.5), 1))->Scale(0.2,0.4,0.3)->Rotate(-M_PI/4,{0,0,1})->Translate(-0.7,0.3,0));

    objects.push_back((new Quadratic(mat4(1,    0,    0,    0,
                                          0,    1,    0,    0,
                                          0,    0,    1,    0,
                                          0,    0,    0, -0.5), 0))->Scale(0.2,0.4,0.3)->Rotate(M_PI/4,{0,0,1})->Translate(0.7,0.3,0));

    // objects.push_back(new Sphere(vec3(0, 0, -0.6), 0.3, 0));

    // objects.push_back(new Sphere(vec3(0, 0, 0), 0.3, 1));
    // objects.push_back(new Sphere(vec3(0, 0, -0.6), 0.3, 0));

    // for (int i = 0; i < 300; i++) {
    //  objects.push_back(new Sphere(vec3(rnd() - 0.5f, rnd() - 0.5f, rnd() - 0.5f), rnd() * 0.1f, i % 3));
    //   //			objects.push_back(new Sphere(vec3(rnd() - 0.5f, rnd() - 0.5f, rnd() - 0.5f), rnd() * 0.1f, 0));
    // }
  }

  void setUniform(RayGpuProgam &shader) {
    shader.setUniformObjects(objects);
    shader.setUniformMaterials(materials);
    shader.setUniformLights(La, lights);
    shader.setUniformCamera(camera);
  }

  void Animate(float dt) { camera.Animate(dt); }

  void onDisplay() override {
    static int nFrames = 0;
    nFrames++;
    static long tStart = glutGet(GLUT_ELAPSED_TIME);
    long tEnd = glutGet(GLUT_ELAPSED_TIME);
    printf("%d msec\n", (tEnd - tStart) / nFrames);

    // vec4 color(159, 123, 189, 255);
    // color = color / 255.0f;
    // glClearColor(color.x, color.y, color.z, color.w);

    // glClearColor(1.0f, 0.5f, 0.8f, 1.5f);  // background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear the screen

    rayGpuProgam.Use();
    setUniform(rayGpuProgam);
    fullScreenTexturedQuad.Draw();

    glutSwapBuffers();
  }
  void onIdle() override {
    Animate(0.01f);
    glutPostRedisplay();
  }
};

}  // namespace simple