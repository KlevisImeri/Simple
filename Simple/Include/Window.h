#pragma once

#include <string>
#include <vector>

#include "GLPP.h"
#include "Scene.h"
#include "vec2.h"

using std::string;
using std::vector;

namespace simple {

class Window {
 public:
  static Window* sWindow;    // Selected window
  static bool initGlutGlew;  // Is glut and glue initilized?
  static long time;          // The global time used for animations
                             // and updated by onIdle

 private:
  unsigned int width, height;  // The windows height and width
  vector<Scene*> scenes;       // A window can have several scenes
  Scene* sScene;               // selected scene
  string name;                 // name of the window
  int ID;                      // ID of the window

  void setGlSettings();  // A function enabling several gl settings.
                         // It can be overriten to enalbes different set of
                         // settings for specific windows
  void setGlutGlew();    // Inicilize Glut/GL and Glew context | used in constructor
  void printGL();        // Prints information about openg gl in the console

  // glut callback functions
  void onDisplay();
  void onIdle();
  void onKeyboard(unsigned char key, int pX, int pY);
  void onKeyboardUp(unsigned char key, int pX, int pY);
  void onMouseMotion(int pX, int pY);
  void onMouse(int button, int state, int pX, int pY);

 public:
  Window(string name = "Simple", unsigned int width = 600,
         unsigned int height = 600);  // General contructor
  ~Window();
  void run();                    // Run the selected window
  void set(unsigned int index);  // Set the selected scene to the sene
                                 // belongingto this index
  void add(Scene* scene);        // Add scene to the window

  // vector<vec4> Window::RayTrace() { return scenes[cS]->render(); }
};

}  // namespace simple
