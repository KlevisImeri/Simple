#include "Simple.h"
using namespace simple;

int main() {
  Window win;  
  Scene scene;
  scene.add(new Curve(0.6, {0, 162, 255}));
  scene.add(new Curve());
  win.add(&scene);
  win.set(&scene);
  win.run();

  return 0;
}
  