#pragma once

#include "GLPP.h"
#include "GPUProgram.h"
#include "Intersectable.h"
#include "vec2.h"
#include "vector"
using std::vector;

namespace simple {

enum Animation { NOT_MOVING, ROTATING, UP_AND_DOWN };

class Shape2D : public Intersectable {
 protected:
  unsigned vao;
  Animation animation;
  mat4 T;
  vector<Shape*> shapes;
  GPUProgram* gpuProgram;

  void upload2F(unsigned vao, unsigned vbo, const vector<vec2>& vertices, int i) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 0, NULL);
  }

 public:
  Shape() {
    // glGenVertexArrays(1, &vao);
    T = ScaleMatrix({1.0, 1.0, 1.0});
  }

  void add(Shape* shape) { shapes.push_back(shape); }

  void animate(Animation anim) { animation = anim; }

  ~Shape() {
    for (Shape* s : shapes) delete s;
  }

  void Render() {
    Animate();
    if (gpuProgram) {
      gpuProgram->Use();
      gpuProgram->setUniform(Animate(), "MVP");
    }
    Draw();
    for (Shape* s : shapes) {
      s->Render(T);
    }
  }
  // virtual ~Shape() = 0;
  void Render(mat4 pT) {  // pT=parentT
    Animate();
    if (gpuProgram) {
      gpuProgram->Use();
      gpuProgram->setUniform(Animate() * pT, "MVP");
    }
    Draw();
    for (Shape* s : shapes) {
      s->Render(T);
    }
  };

  virtual void Draw() {}

  // probaly gonna belong to object
  virtual void onKeyboard(unsigned char key, vec2 pV) {}
  virtual void onKeyboardUp(unsigned char key, vec2 pV) {}
  virtual void onMouseMotion(vec2 pV) {}
  virtual void onMouse(int button, int state, vec2 pV) {}

  mat4 Animate();
};

}  // namespace simple
