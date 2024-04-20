#ifndef SHAPE_H
#define SHAPE_H

#include "GLPP.h"
#include "GPUProgram.h"
#include "vec2.h"
#include "vector"
using std::vector;

namespace simple {

class Shape {

 protected:
  GPUProgram *gpuProgram;
  unsigned vao;

 public:
  // virtual ~Shape() = 0;
  virtual void Render() = 0;
  //probaly gonna belong to object
  virtual void onKeyboard(unsigned char key, vec2 pV) = 0;
  virtual void onKeyboardUp(unsigned char key, vec2 pV) = 0;
  virtual void onMouseMotion(vec2 pV) = 0;
  virtual void onMouse(int button, int state, vec2 pV) = 0;

  void setGpuProgram(GPUProgram *p) { gpuProgram = p; }

  void upload2F(unsigned vao, unsigned vbo, const vector<vec2> &vertices) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * vertices.size(),
                 vertices.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
  }

};


}  // namespace simple

// class Square : public Shape {
//  public:
//   Square() {}
//   void Render() {}
// };

// class Circle : public Shape {
//   static const int nvertices = 10;

//  public:
//   Circle() {}
//   void Render() {}
// };

#endif  // SHAPE_H