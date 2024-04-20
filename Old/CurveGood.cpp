// #include <string>

// #include "Simple.h"

// // global variable you need
// long gtime = 0;
// GPUProgram gpuProgram;
// Curve curve(&gpuProgram);

// // Initialization, create an OpenGL context
// void onInitialization() {
//   glViewport(0, 0, simple::Window::windowWidth, simple::Window::windowHeight);

//   curve.Create();

//   gpuProgram.create(vertexCurve, fragmentCurve, "outColor");
// }

// // Window has become invalid: Redraw
// void onDisplay() {
//   glClearColor(0, 0, 0, 0);     // background color
//   glClear(GL_COLOR_BUFFER_BIT); // clear frame buffer

//   curve.Render();

//   mat4 MVP = ScaleMatrix(vec3(1, 1, 1));
//   gpuProgram.setUniform(MVP, "MVP");
//   glutSwapBuffers(); // exchange buffers for double buffering
// }

// // Idle event indicating that some time elapsed: do animation here
// void onIdle() {
//   gtime = glutGet(GLUT_ELAPSED_TIME);
//   glutPostRedisplay(); // OP will call onDisply to redraw
// }



// void onKeyboard(unsigned char key, int pX, int pY) {}
// void onKeyboardUp(unsigned char key, int pX, int pY) {}
// void onMouseMotion(int pX, int pY) {
//   vec2 cursorPostion = Viewport2Window({pX, pY});
//   curve.MoveControlPoint(cursorPostion);
// }

// void onMouse(int button, int state, int pX, int pY) {       
//   vec2 selectedPoint = Viewport2Window({pX, pY});
//   std::string buttonStat;
//   switch (state) {
//   case GLUT_DOWN:
//     curve.PickControlPoint(selectedPoint);
//     break;
//   case GLUT_UP:
//     curve.ReleaseControlPoint();
//     break;
//   }
// }


