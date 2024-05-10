#pragma once
#include "mat4.h"
#include "Shape.h"
namespace simple {

class Quadratic : Shape {
  mat4 Q;

 public: 
  enum Type { SPHERE }; //iheritace

  Quadratic(Type TYPE, Material* _material) {
    material = _material;
    switch (TYPE) {
      case Type::SPHERE:
      default:
        Q = mat4(
          1, 0, 0, 0, 
          0, 1, 0, 0, 
          0, 0, 1, 0, 
          0, 0, 0, 1
        );
    }
  }

  void Draw() override {}

  Hit intersect(const Ray& ray) override {
    Hit hit;
    vec4 s(ray.start, 1);
    vec4 d(ray.dir, 0);
    float a = dot(d * Q, d);
    float b = dot(s * Q, d) * 2.0f;
    float c = dot(s * Q, s);
    float discr = b * b - 4.0f * a * c;
    if (discr < 0) return hit;
    float sqrt_discr = sqrtf(discr);
    float t1 = (-b + sqrt_discr) / 2.0f / a;  // t1 >= t2 for sure
    float t2 = (-b - sqrt_discr) / 2.0f / a;
    if (t1 <= 0) return hit;
    hit.t = (t2 > 0) ? t2 : t1;
    hit.position = ray.start + ray.dir * hit.t;
    hit.normal = vec3(vec4(hit.position, 1) * Q);
    hit.material = material;
    return hit;
  };

  // Quadratic* Scale(float x, float y, float z) {
  //   mat4 MI = ScaleMatrix(vec3(1/x,1/y,1/z));
  //   Q = MI*Q*T(MI);
  // }
  // Quadratic* Translate(vec3 t) {

  //   Q = TranslateMatrix(-1*t)*Q*TranslateMatrix(-1*t);
  // }
  // Quadratic* Rotate() {

  // }
};

}  // namespace simple