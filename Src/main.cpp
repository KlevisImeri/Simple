#include "Simple.h"
using namespace simple;


class RenderScene : public Scene2D {
 public:
  RenderScene() { add(new Curve()); }
};

class QuadScene : public Scene2D {
 public:
  QuadScene() { 
    // add(new TexturedQuad("brickwall.bmp")); 
    add(new Curve()); 
  }
};

int main() {
  Window win0;
  win0.add(new RayScene());
  win0.run();

  // Window win1;
  // win1.add(new QuadScene());

  return 0;
}

