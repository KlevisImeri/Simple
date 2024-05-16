#pragma once

#include "Ray.h"
#include "vec3.h"

namespace simple {

struct Material {
  vec3 ka, kd, ks;
  float shininess;
  Material(vec3 _kd, vec3 _ks, float _shininess) : ka(_kd * M_PI), kd(_kd), ks(_ks) { shininess = _shininess; }
};

struct Hit {
  float t;
  vec3 position, normal;
  Material* material;
  Hit() { t = -1; }
};

class Intersectable {
 protected:
  Material* material;

 public:
  virtual Hit intersect(const Ray& ray) = 0;
};

}  // namespace simple