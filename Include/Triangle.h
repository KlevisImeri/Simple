#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "GLPP.h"
#include "vec3.h"

class Triangle {
  unsigned int vao;

  void bufferVertices(vec3 vertices[], const unsigned int vbo);
  void bufferColors(vec3 colors[], const unsigned int vbo);

 public:
  Triangle();
  void Create(vec3 x = {-0.5f, -0.5f, 1.0f}, vec3 y = {0.0f, 0.36f, 1.0f},
              vec3 z = {0.5f, -0.5f, 1.0f}, vec3 c1 = {1.0f, 0.0f, 0.0f},
              vec3 c2 = {0.0f, 1.0f, 0.0f}, vec3 c3 = {0.0f, 0.0f, 1.0f});
  void Render();
};

#endif // TRIANGLE_H
