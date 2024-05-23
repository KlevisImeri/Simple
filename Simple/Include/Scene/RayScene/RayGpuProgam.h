#pragma once


#include "GPUProgram.h"
#include "Material.h"
#include "Sphere.h"
#include "Light.h"
#include "Camera.h"


namespace simple {

class RayGpuProgam : public GPUProgram {
public:
	void setUniformMaterials(const std::vector<Material*>& materials) {
		char name[256];
		for (unsigned int mat = 0; mat < materials.size(); mat++) {
			sprintf(name, "materials[%d].ka", mat); setUniform(materials[mat]->ka, name);
			sprintf(name, "materials[%d].kd", mat); setUniform(materials[mat]->kd, name);
			sprintf(name, "materials[%d].ks", mat); setUniform(materials[mat]->ks, name);
			sprintf(name, "materials[%d].shininess", mat); setUniform(materials[mat]->shininess, name);
			sprintf(name, "materials[%d].F0", mat); setUniform(materials[mat]->F0, name);
			sprintf(name, "materials[%d].n", mat); setUniform(materials[mat]->n, name);
			sprintf(name, "materials[%d].type", mat); setUniform((int)materials[mat]->type, name);
		}
	}

	void setUniformLights(const vec3& La, const std::vector<Light*>& lights) {
		setUniform(La, "La");
		setUniform((int)lights.size(), "nLights");
		char name[256];
		for (unsigned int l = 0; l < lights.size(); l++) {
			sprintf(name, "lights[%d].Le", l); setUniform(lights[l]->Le, name);
			sprintf(name, "lights[%d].direction", l); setUniform(lights[l]->direction, name);
		}
	}

	void setUniformCamera(const Camera& camera) {
		setUniform(camera.eye, "wEye");
		setUniform(camera.lookat, "wLookAt");
		setUniform(camera.right, "wRight");
		setUniform(camera.up, "wUp");
	}

	// void setUniformObjects(const std::vector<Sphere*>& objects) {
	// 	setUniform((int)objects.size(), "nObjects");
	// 	char name[256];
	// 	for (unsigned int o = 0; o < objects.size(); o++) {
	// 		sprintf(name, "objects[%d].center", o);  setUniform(objects[o]->center, name);
	// 		sprintf(name, "objects[%d].radius", o);  setUniform(objects[o]->radius, name);
	// 		sprintf(name, "objects[%d].mat", o);  setUniform(objects[o]->mat, name);
	// 	}
	// }

  void setUniformObjects(const std::vector<Quadratic*>& objects) {
		setUniform((int)objects.size(), "nObjects");
		char name[256];
		for (unsigned int o = 0; o < objects.size(); o++) {
			sprintf(name, "objects[%d].Q", o);  setUniform(objects[o]->Q, name);
			sprintf(name, "objects[%d].mat", o);  setUniform(objects[o]->mat, name);
		}
	}
};

}