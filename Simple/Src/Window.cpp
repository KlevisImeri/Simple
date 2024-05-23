#include "Window.h"

#include <GL/freeglut.h>
#include <stdio.h>

#include "mat4.h"

namespace simple {

/*----------------------Static-----------------------*/
Window *Window::sWindow;
bool Window::initGlutGlew = false;
long Window::time;
/*----------------------Static-----------------------*/

/*---------------------------------------------------*/
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

void Window::setGlutGlew() {
  if (initGlutGlew) return;
  char *argv[] = {};
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

// DisjointUnionSet
void Window::onDisplay() {
  if (sScene) sScene->onDisplay();
}
void Window::onIdle() {
  time = glutGet(GLUT_ELAPSED_TIME);
  if (sScene) sScene->onIdle();
  glutPostRedisplay();  // OP will call onDisplay to redraw
}
void Window::onKeyboard(unsigned char key, int pX, int pY) {
  if (sScene) sScene->onKeyboard(key, Viewport2Window(width, height, {(float)pX, (float)pY}));
}
void Window::onKeyboardUp(unsigned char key, int pX, int pY) {
  if (sScene) sScene->onKeyboardUp(key, Viewport2Window(width, height, {(float)pX, (float)pY}));
}
void Window::onMouseMotion(int pX, int pY) {
  if (sScene) sScene->onMouseMotion(Viewport2Window(width, height, {(float)pX, (float)pY}));
}
void Window::onMouse(int button, int state, int pX, int pY) {
  if (sScene) sScene->onMouse(button, state, Viewport2Window(width, height, {(float)pX, (float)pY}));
}
/*---------------------------------------------------*/

/*---------------------------------------------------*/
Window::Window(std::string name, unsigned int width, unsigned int height) : name(name), width(width), height(height) {
  setGlutGlew();
  setGlSettings();

  printGL();

  sWindow = this;
  
  glutDisplayFunc([]() { sWindow->onDisplay(); });
  glutIdleFunc([]() { sWindow->onIdle(); });
  glutKeyboardFunc([](unsigned char key, int x, int y) { sWindow->onKeyboard(key, x, y); });
  glutKeyboardUpFunc([](unsigned char key, int x, int y) { sWindow->onKeyboardUp(key, x, y); });
  glutMouseFunc([](int button, int state, int x, int y) { sWindow->onMouse(button, state, x, y); });
  glutMotionFunc([](int x, int y) { sWindow->onMouseMotion(x, y); });
}

Window::~Window() {
  for (Scene *s : scenes) delete s;
}
/*---------------------------------------------------*/

/*---------------------------------------------------*/
void Window::run() { glutMainLoop(); }

void Window::set(unsigned int index) {
  if (index < scenes.size()) sScene = scenes[index];
}

void Window::add(Scene *scene) {
  scenes.push_back(scene);
  set(scenes.size() - 1);
}
/*---------------------------------------------------*/

}  // namespace simple