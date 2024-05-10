#pragma once
#include "vec3.h"
#include "Intersectable.h"
namespace simple {

struct Sphere : public Shape {
  vec3 center;
  float radius;

  Sphere(const vec3& _center, float _radius, Material* _material) {
    center = _center;
    radius = _radius;
    material = _material;
  }

  Hit intersect(const Ray& ray) {
    Hit hit;
    vec3 dist = ray.start - center;
    float a = dot(ray.dir, ray.dir);
    float b = dot(dist, ray.dir) * 2.0f;
    float c = dot(dist, dist) - radius * radius;
    float discr = b * b - 4.0f * a * c;
    if (discr < 0) return hit;
    float sqrt_discr = sqrtf(discr);
    float t1 = (-b + sqrt_discr) / 2.0f / a;  // t1 >= t2 for sure
    float t2 = (-b - sqrt_discr) / 2.0f / a;
    if (t1 <= 0) return hit;
    hit.t = (t2 > 0) ? t2 : t1;
    hit.position = ray.start + ray.dir * hit.t;
    hit.normal = (hit.position - center) * (1.0f / radius);
    hit.material = material;
    return hit;
  }
};

}  // namespace simple