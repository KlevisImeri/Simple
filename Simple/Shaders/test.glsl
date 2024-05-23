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
  }

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

	const int nMaxObjects = 300, nMaxLights = 2;

	uniform vec3 wEye; 
	uniform int nLights;
	uniform Light lights[nMaxLights]; 
	uniform vec3 La;    
	uniform Material materials[3];  // diffuse, specular, ambient ref
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
		float c = dot(start, start);
		float discr = b * b - 4.0f * a * c;
		if (discr < 0) return hit;
		float sqrt_discr = sqrt(discr);
		float t1 = (-b + sqrt_discr) / 2.0f / a;	// t1 >= t2 for sure
		float t2 = (-b - sqrt_discr) / 2.0f / a;
		if (t1 <= 0) return hit;
		hit.t = (t2 > 0) ? t2 : t1;
		hit.position = ray.start + ray.dir * hit.t;
		hit.normal =vec3(Q*vec4(hit.position,1.0));
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