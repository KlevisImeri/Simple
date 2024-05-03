#include "Window.h"

namespace simple {


void Scene::onDisplay() {
  glClearColor(0, 0, 0, 0);      // background color
  glClear(GL_COLOR_BUFFER_BIT);  // clear frame buffer
  for (Shape* s : shapes) s->Render();
  glutSwapBuffers();  // exchange buffers for double buffering
}

void Scene::onIdle() {
  Window::time = glutGet(GLUT_ELAPSED_TIME);
  glutPostRedisplay();  // OP will call onDisplay to redraw
}

void Scene::onKeyboard(unsigned char key, vec2 pP) {
  vec2 cP = Window::Viewport2Window(pP);
  for (Shape* s : shapes) s->onKeyboard(key, cP);
}

void Scene::onKeyboardUp(unsigned char key, vec2 pP) {
  vec2 cP = Window::Viewport2Window(pP);
  for (Shape* s : shapes) s->onKeyboardUp(key, cP);
}

void Scene::onMouseMotion(vec2 pP) {
  vec2 cP = Window::Viewport2Window(pP);
  for (Shape* s : shapes) s->onMouseMotion(cP);
}

void Scene::onMouse(int button, int state, vec2 pP) {
  vec2 cP = Window::Viewport2Window(pP);
  for (Shape* s : shapes) s->onMouse(button, state, cP);
}

}  // namespace simple
