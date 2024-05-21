#pragma once

#include "vec3.h"
#include "vec4.h"

namespace simple {

struct mat4 {  // row-major matrix 4x4

  vec4 rows[4];

 public:
  mat4() {}
  mat4(float m00, float m01, float m02, float m03, 
       float m10, float m11, float m12, float m13, 
       float m20, float m21, float m22, float m23,
       float m30, float m31, float m32, float m33) {
    rows[0][0] = m00;
    rows[0][1] = m01;
    rows[0][2] = m02;
    rows[0][3] = m03;
    rows[1][0] = m10;
    rows[1][1] = m11;
    rows[1][2] = m12;
    rows[1][3] = m13;
    rows[2][0] = m20;
    rows[2][1] = m21;
    rows[2][2] = m22;
    rows[2][3] = m23;
    rows[3][0] = m30;
    rows[3][1] = m31;
    rows[3][2] = m32;
    rows[3][3] = m33;
  }
  mat4(vec4 it, vec4 jt, vec4 kt, vec4 ot) {
    rows[0] = it;
    rows[1] = jt;
    rows[2] = kt;
    rows[3] = ot;
  }

  vec4 &operator[](int i) { return rows[i]; }
  vec4 operator[](int i) const { return rows[i]; }
  operator float *() const { return (float *)this; }
};

inline mat4 T(mat4 M) {
    return mat4(
      M.rows[0][0], M.rows[1][0], M.rows[2][0], M.rows[3][0],
      M.rows[0][1], M.rows[1][1], M.rows[2][1], M.rows[3][1],
      M.rows[1][2], M.rows[2][2], M.rows[2][2], M.rows[3][2],
      M.rows[0][3], M.rows[1][3], M.rows[2][3], M.rows[3][3]
    );
  }
inline vec4 operator*(const vec4 &v, const mat4 &mat) {
  return v[0] * mat[0] + v[1] * mat[1] + v[2] * mat[2] + v[3] * mat[3];
}

inline mat4 operator*(const mat4 &left, const mat4 &right) {
  mat4 result;
  for (int i = 0; i < 4; i++) result.rows[i] = left.rows[i] * right;
  return result;
}


inline mat4 TranslateMatrix(vec3 t) {
  return mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0),
              vec4(t.x, t.y, t.z, 1));
}

inline mat4 ScaleMatrix(vec3 s) {
  return mat4(vec4(s.x, 0, 0, 0), vec4(0, s.y, 0, 0), vec4(0, 0, s.z, 0),
              vec4(0, 0, 0, 1));
}

inline mat4 RotationMatrix(float angle, vec3 w) {
  float c = cosf(angle), s = sinf(angle);
  w = normalize(w);
  return mat4(
      vec4(c * (1 - w.x * w.x) + w.x * w.x, w.x * w.y * (1 - c) + w.z * s,
           w.x * w.z * (1 - c) - w.y * s, 0),
      vec4(w.x * w.y * (1 - c) - w.z * s, c * (1 - w.y * w.y) + w.y * w.y,
           w.y * w.z * (1 - c) + w.x * s, 0),
      vec4(w.x * w.z * (1 - c) + w.y * s, w.y * w.z * (1 - c) - w.x * s,
           c * (1 - w.z * w.z) + w.z * w.z, 0),
      vec4(0, 0, 0, 1));
}

inline vec2 Viewport2Window(int WIDTH,   int HEIGHT, vec2 pixel) { 
  return {2.0f * pixel.x / WIDTH - 1, 1.0f - 2.0f * pixel.y / HEIGHT}; 
}

}
