#include "Window.h"

#include <GL/freeglut.h>
#include <stdio.h>

namespace simple {

vector<Window*> Window::windows;
int Window::cW;
int Window::WIDTH;
int Window::HEIGHT;
long Window::time;

vec2 Window::Viewport2Window(vec2 pixel) {
  return {2.0f * pixel.x / WIDTH - 1, 1.0f - 2.0f * pixel.y / HEIGHT};
}

void Window::onDisplay() { windows[cW]->scenes[windows[cW]->cS]->onDisplay(); }

void Window::onIdle() { windows[cW]->scenes[windows[cW]->cS]->onIdle(); }

void Window::onKeyboard(unsigned char key, int pX, int pY) {
  windows[cW]->scenes[windows[cW]->cS]->onKeyboard(key, {(float)pX, (float)pY});
}

void Window::onKeyboardUp(unsigned char key, int pX, int pY) {
  windows[cW]->scenes[windows[cW]->cS]->onKeyboardUp(key, {(float)pX, (float)pY});
}

void Window::onMouseMotion(int pX, int pY) {
  windows[cW]->scenes[windows[cW]->cS]->onMouseMotion({(float)pX, (float)pY});
}

void Window::onMouse(int button, int state, int pX, int pY) {
  windows[cW]->scenes[windows[cW]->cS]->onMouse(button, state, {(float)pX, (float)pY});
}

Window::Window(std::string name, unsigned int width, unsigned int height)
    : name(name), width(width), height(height) {
  setGlutGlewGL();
  setGlSettings();

  cS = 0;
  ID = windows.size();
  windows.push_back(this);

  glutDisplayFunc(glutDisplayWrapper);
  glutMouseFunc(glutMouseWrapper);
  glutIdleFunc(glutIdleWrapper);
  glutKeyboardFunc(glutKeyboardWrapper);
  glutKeyboardUpFunc(glutKeyboardUpWrapper);
  glutMotionFunc(glutMouseMotionWrapper);
}

Window::~Window() {
  for (Scene* s : scenes) delete s;
}

void Window::run() {
  cW = ID;
  WIDTH = width;
  HEIGHT = height;
  glutMainLoop();
}

void Window::set(Scene* scene) {
  if (scene->ID < scenes.size()) cS = scene->ID;
}

void Window::add(Scene* scene) {
  scene->ID = scenes.size();
  scenes.push_back(scene);
}

void Window::setGlSettings() {
  glViewport(0, 0, width, height);
  // glEnable(GL_DEPTH_TEST);
  // glDepthFunc(GL_LEQUAL);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
  // glDisable(GL_CULL_FACE);
  // glEnable(GL_MULTISAMPLE);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPointSize(8);
  glLineWidth(5);
}

void Window::setGlutGlewGL() {
  char* argv[] = {};
  int argc = 0;
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(name.c_str());
  glewExperimental = true;
  glewInit();
  printGL();
}

void Window::printGL() {
  int majorVersion, minorVersion;
  printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
  printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
  printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));
  glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
  glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
  printf("GL Version (integer) : %d.%d\n", majorVersion, minorVersion);
  printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void Window::glutDisplayWrapper() { onDisplay(); }

void Window::glutIdleWrapper() { onIdle(); }

void Window::glutKeyboardWrapper(unsigned char key, int pX, int pY) {
  onKeyboard(key, pX, pY);
}

void Window::glutKeyboardUpWrapper(unsigned char key, int pX, int pY) {
  onKeyboardUp(key, pX, pY);
}

void Window::glutMouseMotionWrapper(int pX, int pY) { onMouseMotion(pX, pY); }

void Window::glutMouseWrapper(int button, int state, int pX, int pY) {
  onMouse(button, state, pX, pY);
}

}  // namespace simple