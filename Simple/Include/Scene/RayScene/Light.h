#pragma once
#include "vec3.h"
namespace simple {

struct Light {
//---------------------------
	vec3 direction;
	vec3 Le;
	Light(vec3 _direction, vec3 _Le) {
		direction = normalize(_direction);
		Le = _Le;
	}
};

}  // namespace simple