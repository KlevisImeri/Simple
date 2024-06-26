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

  // Window win1;
  // win1.add(new QuadScene());

  win0.run();
  return 0;
}

