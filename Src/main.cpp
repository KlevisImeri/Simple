#include "Simple.h"
using namespace simple;


class RenderScene : public Scene {
 public:
  RenderScene() { add(new Sphere()); }
};

class QuadScene : public Scene {
 public:
  QuadScene(vector<vec4> image) { add(new TexturedQuad(image)); }
};

int main() {
  Window win0;
  Window win1;
  win0.add(new RenderScene());
  win1.add(new QuadScene(win0.RayTrace()));
  win1.run();
  return 0;
}
