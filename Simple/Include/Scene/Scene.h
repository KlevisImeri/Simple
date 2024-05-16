#pragma once

#include "vec2.h"

namespace simple {

class Scene {
 public:
  virtual void onDisplay() = 0;
  virtual void onIdle() = 0;
  virtual void onKeyboard(unsigned char key, vec2 pP) = 0;
  virtual void onKeyboardUp(unsigned char key, vec2 pP) = 0;
  virtual void onMouseMotion(vec2 pP) = 0;
  virtual void onMouse(int button, int state, vec2 pP) = 0;
};

}  // namespace simple
