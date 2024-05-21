#include "Scene2D.h"

namespace simple {

void Scene2D::add(Shape* shape) { shapes.push_back(shape); }

void Scene2D::onDisplay() {
  glClearColor(0, 0, 0, 0);      // background color
  glClear(GL_COLOR_BUFFER_BIT);  // clear frame buffer
  for (Shape* s : shapes) s->Render();
  glutSwapBuffers();  // exchange buffers for double buffering
}

void Scene2D::onIdle() {}

void Scene2D::onKeyboard(unsigned char key, vec2 cP) {
  for (Shape* s : shapes) s->onKeyboard(key, cP);
}

void Scene2D::onKeyboardUp(unsigned char key, vec2 cP) {
  for (Shape* s : shapes) s->onKeyboardUp(key, cP);
}

void Scene2D::onMouseMotion(vec2 cP) {
  for (Shape* s : shapes) s->onMouseMotion(cP);
}

void Scene2D::onMouse(int button, int state, vec2 cP) {
  for (Shape* s : shapes) s->onMouse(button, state, cP);
}

}  // namespace simple