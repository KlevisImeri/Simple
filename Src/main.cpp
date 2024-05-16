#include "Simple.h"
using namespace simple;


class RenderScene : public Scene2D {
 public:
  RenderScene() { add(new Sphere()); }
};

class QuadScene : public Scene2D {
 public:
  QuadScene(vector<vec4> image) { add(new TexturedQuad(image)); }
};

int main() {
  Window win0;
  win0.add(new RenderScene());
  win1.add(new QuadScene(win0.RayTrace()));
  win1.run();
  return 0;
}
