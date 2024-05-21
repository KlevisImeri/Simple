#pragma once

#include "GLPP.h"
#include "GPUProgram.h"
#include "Intersectable.h"
#include "vec2.h"
#include "vector"
using std::vector;

namespace simple {

enum Animation { NOT_MOVING, ROTATING, UP_AND_DOWN };

class Shape {
 protected:
  unsigned vao;             // Vao of the shape
  Animation animation;      // Animation type
  mat4 T;                   // Where the shape is on the screeen
  vector<Shape*> shapes;  // Shapes it has
  GPUProgram* gpuProgram;   // The Shader

  // To upload ot the arrays to the gpu
  void upload2F(unsigned vao, int index, unsigned vbo, const vector<vec2>& vertices);
  mat4 Animate();  // Animating | Chaning the T matrix

 public:
  Shape();
  ~Shape();

  void add(Shape* shape);
  void animate(Animation anim);  // Set the animation

  void Render(mat4 pT = ScaleMatrix({1.0, 1.0, 1.0}));  // Rendering Generic

  /*-----------------------Implement-------------------------*/
  // Drawing the shape
  virtual void Draw() = 0;  // Draw the shape here
  // Optional listeners
  virtual void onKeyboard(unsigned char key, vec2 pV) {}
  virtual void onKeyboardUp(unsigned char key, vec2 pV) {}
  virtual void onMouseMotion(vec2 pV) {}
  virtual void onMouse(int button, int state, vec2 pV) {}
  /*-----------------------Implement-------------------------*/
};

}  // namespace simple
