#include "Simple.h"
using namespace simple;

class SquareCurve : public Shape {
 public:
  SquareCurve() {
    auto c = new Curve();
    c->animate(Animation::ROTATING);
    add(c);
  }
  void Draw() override {}
};

class ExScene : public Scene {
 public:
  ExScene() { add(new SquareCurve()); }
};

int main() {
  Window win;
  win.add(new ExScene());
  win.run();
  return 0;
}
