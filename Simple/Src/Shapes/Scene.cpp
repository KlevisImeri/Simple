#include "../../Include/Scene/Scene.h"
#include "../../Include/Window.h"

namespace simple {

Scene::Scene() {
  gpuProgram = new GPUProgram();
  gpuProgram->create(vertexCurve, fragmentCurve, "outColor");
}

Scene::~Scene() {
  for (Shape* s : shapes) delete s;
}

void Scene::add(Shape* shape) {
  shape->setGpuProgram(gpuProgram);
  shapes.push_back(shape);
}

void Scene::onDisplay() {
  glClearColor(0, 0, 0, 0);      // background color
  glClear(GL_COLOR_BUFFER_BIT);  // clear frame buffer
  mat4 MVP = ScaleMatrix(vec3(1, 1, 1));
  gpuProgram->setUniform(MVP, "MVP");
  for (Shape* s : shapes) s->Render();
  glutSwapBuffers();  // exchange buffers for double buffering
}

void Scene::onIdle() {
  gtime = glutGet(GLUT_ELAPSED_TIME);
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
