#ifndef SCENE_H
#define SCENE_H

#include "GpuProgram.h"
#include "Shape.h"
#include "fragmentShader.h"
#include "vertexShader.h"
#include <vector>
using std::vector;

namespace simple {

class Scene {
private:
    long gtime = 0;
    vector<Shape*> shapes;
    GPUProgram* gpuProgram;
    unsigned int width, height = 600;

public:
    int ID;

    Scene();
    ~Scene();
    void add(Shape* shape);
    void onDisplay();
    void onIdle();
    void onKeyboard(unsigned char key, vec2 pP);
    void onKeyboardUp(unsigned char key, vec2 pP);
    void onMouseMotion(vec2 pP);
    void onMouse(int button, int state, vec2 pP);
};

} // namespace simple

#endif // SCENE_H
