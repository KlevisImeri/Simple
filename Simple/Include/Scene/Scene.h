#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "GpuProgram.h"
#include "Shape.h"
#include "fragmentShader.h"
#include "vertexShader.h"
using std::vector;

namespace simple {

class Scene {  
  private:
  vector<Shape*> shapes;

  protected:
  void add(Shape* shape) {shapes.push_back(shape);}
  
 public:
  int ID;

  ~Scene() {
    for(Shape* s : shapes) delete s;
  }
  void onDisplay();
  void onIdle();
  void onKeyboard(unsigned char key, vec2 pP);
  void onKeyboardUp(unsigned char key, vec2 pP);
  void onMouseMotion(vec2 pP);
  void onMouse(int button, int state, vec2 pP);
};

}  // namespace simple

#endif  // SCENE_H
