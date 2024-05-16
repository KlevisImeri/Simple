#pragma once
#include "Ray.h"
#include "vec3.h"
namespace simple {
#include "window.h"

class Camera {
  vec3 eye, lookat, right, up;

 public:
  Camera(vec3 _eye, vec3 _lookat, vec3 vup, float fov) {
    set(_eye, _lookat, vup, fov);
  }
  void set(vec3 _eye, vec3 _lookat, vec3 vup, float fov) {
    eye = _eye;
    lookat = _lookat;
    vec3 w = eye - lookat;
    float focus = length(w);
    right = normalize(cross(vup, w)) * focus * tanf(fov / 2);
    up = normalize(cross(w, right)) * focus * tanf(fov / 2);
  }
  
  Ray getRay(int X, int Y) {
    vec3 dir = lookat + right * (2.0f * (X + 0.5f) / Window::WIDTH - 1) +
               up * (2.0f * (Y + 0.5f) / Window::HEIGHT - 1) - eye;
    return Ray(eye, dir);
  }
};

//need to seperate the files here

}  // namespace simple