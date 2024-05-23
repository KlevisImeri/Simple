#pragma once
#include "Intersectable.h"
#include "vec3.h"
namespace simple {

// struct Sphere : public Intersectable {
//   vec3 center;
//   float radius;

//   Sphere(
//       vec3 _center = {0,0,1}, 
//       float _radius = 1, 
//       Material* _material = new Material({40,40,40},{20,20,20}, 10)
//       ) {
//     center = _center;
//     radius = _radius;
//     material = _material;
//   }

//   Hit intersect(const Ray& ray) {
//     Hit hit;
//     vec3 dist = ray.start - center;
//     float a = dot(ray.dir, ray.dir);
//     float b = dot(dist, ray.dir) * 2.0f;
//     float c = dot(dist, dist) - radius * radius;
//     float discr = b * b - 4.0f * a * c;
//     if (discr < 0) return hit;
//     float sqrt_discr = sqrtf(discr);
//     float t1 = (-b + sqrt_discr) / 2.0f / a;  // t1 >= t2 for sure
//     float t2 = (-b - sqrt_discr) / 2.0f / a;
//     if (t1 <= 0) return hit;
//     hit.t = (t2 > 0) ? t2 : t1;
//     hit.position = ray.start + ray.dir * hit.t;
//     hit.normal = (hit.position - center) * (1.0f / radius);
//     hit.material = material;
//     return hit;
//   }
// };

// struct Sphere {
// //---------------------------
// 	vec3 center;
// 	float radius;
// 	int mat;

// 	Sphere(const vec3& _center, float _radius, int matIdx) { center = _center; radius = _radius; mat = matIdx; }
// };
}  // namespace simple