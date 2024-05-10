#pragma once
#include "vec3.h"
namespace simple {

struct Ray {
  vec3 start, dir;
  Ray(vec3 _start, vec3 _dir) {
    start = _start;
    dir = normalize(_dir);
  }
};

}  // namespace simple
