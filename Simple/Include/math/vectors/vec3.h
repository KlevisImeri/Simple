#pragma once

#include "vec2.h"

namespace simple {

struct vec3 {
  float x, y, z;
  vec3(float x0 = 0, float y0 = 0, float z0 = 0) {
    x = x0;
    y = y0;
    z = z0;
  }
  vec3(vec2 v) {
    x = v.x;
    y = v.y;
    z = 0;
  }
  vec3 operator*(float a) const { return vec3(x * a, y * a, z * a); }
  vec3 operator/(float a) const { return vec3(x / a, y / a, z / a); }
  vec3 operator+(const vec3 &v) const {
    return vec3(x + v.x, y + v.y, z + v.z);
  }
  vec3 operator-(const vec3 &v) const {
    return vec3(x - v.x, y - v.y, z - v.z);
  }
  vec3 operator*(const vec3 &v) const {
    return vec3(x * v.x, y * v.y, z * v.z);
  }
  vec3 operator-() const { return vec3(-x, -y, -z); }
};
inline float dot(const vec3 &v1, const vec3 &v2) {
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
inline float length(const vec3 &v) { return sqrtf(dot(v, v)); }
inline vec3 normalize(const vec3 &v) { return v * (1 / length(v)); }
inline vec3 cross(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
              v1.x * v2.y - v1.y * v2.x);
}
inline vec3 operator*(float a, const vec3 &v) {
  return vec3(v.x * a, v.y * a, v.z * a);
}

}  // namespace simple
