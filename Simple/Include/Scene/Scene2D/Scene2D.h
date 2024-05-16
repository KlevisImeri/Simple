#pragma once

#include "Scene.h"
#include "Shape.h"
#include "vector"
using std::vector;

namespace simple {

class Scene2D : public Scene {
  vector<Shape*> shapes;

 public:
  void add(Shape* shape); //add the shapes to the scene

  virtual void onDisplay() override;
  virtual void onIdle() override;
  virtual void onKeyboard(unsigned char key, vec2 pP) override;
  virtual void onKeyboardUp(unsigned char key, vec2 pP) override;
  virtual void onMouseMotion(vec2 pP) override;
  virtual void onMouse(int button, int state, vec2 pP) override;
};

}  // namespace simple