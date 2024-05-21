#pragma once

#include "Ray.h"
#include "vec3.h"
#include "Material.h"

namespace simple {

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