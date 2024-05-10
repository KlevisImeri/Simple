#include "Window.h"

namespace simple {

mat4 Shape::Animate() {
  float alpha = 0.0;
  switch (animation) {
    case NOT_MOVING:
      return T;
    case ROTATING:
      alpha = M_PI * Window::time / 100000.0;
      return RotationMatrix(alpha, vec3(0.0, 0.0, 1.0)) * T;
      break;
    case UP_AND_DOWN:
      alpha = M_PI / 4.0 * cos(Window::time / 1000.0);
      return RotationMatrix(alpha, vec3(0.0, 0.0, 1.0)) * T;
      break;
    default:
      return T;
  }
}

}  // namespace simple