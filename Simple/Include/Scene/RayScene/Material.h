#pragma once

#include "vec3.h"

namespace simple {

struct Material {
	vec3 ka, kd, ks;
	float  shininess;
	vec3 F0;
	float n;
	enum { ROUGH, REFLECTIVE, REFLECTIVE_REFRACTIVE} type;
};

//---------------------------
struct RoughMaterial : Material {
//---------------------------
	RoughMaterial(vec3 _kd, vec3 _ks, float _shininess) {
		ka = _kd * M_PI;
		kd = _kd;
		ks = _ks;
		shininess = _shininess;
		type = ROUGH;
	}
};

//---------------------------
struct SmoothReflectorMaterial : Material {
//---------------------------
	SmoothReflectorMaterial(vec3 _F0) {
		F0 = _F0;
		n = 1.0f;
		type = REFLECTIVE;
	}
};

//---------------------------
struct SmoothRefractorMaterial : Material {
//---------------------------
	SmoothRefractorMaterial(vec3 _F0, float _n) {
		F0 = _F0;
		n = _n;
		type = REFLECTIVE_REFRACTIVE;
	}
};

}  // namespace simple