
#include "Shape.h"
#include "Window.h"

namespace simple {
/*---------------------------------------------------*/

void Shape::upload2F(unsigned vao, int index, unsigned vbo, const vector<vec2>& vertices) {
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

mat4 Shape::Animate() {
  float alpha = 0.0;
  switch (animation) {
    case NOT_MOVING:
      return T;
    case ROTATING:
      alpha = M_PI * Window::time / 100000.0;
      return RotationMatrix(alpha, vec3(0.0, 0.0, 1.0)) * T;
      break;
    case UP_AND_DOWN:
      alpha = M_PI / 4.0 * cos(Window::time / 1000.0);
      return RotationMatrix(alpha, vec3(0.0, 0.0, 1.0)) * T;
      break;
    default:
      return T;
  }
}

/*---------------------------------------------------*/

Shape::Shape() {
  // glGenVertexArrays(1, &vao);
  T = ScaleMatrix({1.0, 1.0, 1.0});
}

Shape::~Shape() {
  for (Shape* s : shapes) {
    delete s;
  }
}

void Shape::add(Shape* shape) { shapes.push_back(shape); }

void Shape::animate(Animation anim) { animation = anim; }

void Shape::Render(mat4 pT) {
  Animate();
  if (gpuProgram) {
    gpuProgram->Use();
    gpuProgram->setUniform(Animate() * pT, "MVP");
  }
  Draw();
  for (Shape* s : shapes) {
    s->Render(T);
  }
}

/*---------------------------------------------------*/

}  // namespace simple