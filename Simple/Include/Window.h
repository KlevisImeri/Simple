#ifndef SIMPLE_WINDOW_H
#define SIMPLE_WINDOW_H

#include <string>
#include <vector>

#include "GLPP.h"
#include "../../Include/Scene/Scene.h"
#include "vec2.h"

using std::string;
using std::vector;

namespace simple {

class Window {
 public:
  static vector<Window*> windows;
  static int cW;
  static int WIDTH;
  static int HEIGHT;

  static vec2 Viewport2Window(vec2 pixel);

  static void onDisplay();
  static void onIdle();
  static void onKeyboard(unsigned char key, int pX, int pY);
  static void onKeyboardUp(unsigned char key, int pX, int pY);
  static void onMouseMotion(int pX, int pY);
  static void onMouse(int button, int state, int pX, int pY);

  Window(string name = "Simple", unsigned int width = 600,
         unsigned int height = 600);
  ~Window();
  void run();
  void set(Scene* scene);
  void add(Scene* scene);

 private:
  unsigned int width, height;
  vector<Scene*> scenes;
  int cS;
  string name;
  int ID;

  void setGlSettings();
  void setGlutGlewGL();
  void printGL();

  static void glutDisplayWrapper();
  static void glutIdleWrapper();
  static void glutKeyboardWrapper(unsigned char key, int pX, int pY);
  static void glutKeyboardUpWrapper(unsigned char key, int pX, int pY);
  static void glutMouseMotionWrapper(int pX, int pY);
  static void glutMouseWrapper(int button, int state, int pX, int pY);
};

}  // namespace simple

#endif  // SIMPLE_WINDOW_H
