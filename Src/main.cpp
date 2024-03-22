#include <string>

#include "Simple.h"

int main(int argc, char *argv[]) { 
  setup(&argc, argv); 

}

// global variable yuou need
GPUProgram gpuProgram;
long time = 0;
Curve curve(&gpuProgram);

// Initialization, create an OpenGL context
void onInitialization() {
  glViewport(0, 0, windowWidth, windowHeight);

  curve.Create();

  gpuProgram.create(vertexCurve, fragmentCurve, "outColor");
}

// Window has become invalid: Redraw
void onDisplay() {
  glClearColor(0, 0, 0, 0);      // background color
  glClear(GL_COLOR_BUFFER_BIT);  // clear frame buffer

  curve.Render();

  mat4 MVP = ScaleMatrix(vec3(1, 1, 1));
  gpuProgram.setUniform(MVP, "MVP");
  glutSwapBuffers();  // exchange buffers for double buffering
}

void onKeyboard(unsigned char key, int pX, int pY) {}
void onKeyboardUp(unsigned char key, int pX, int pY) {}
void onMouseMotion(int pX, int pY) {
  float cX = 2.0f * pX / windowWidth - 1;
  float cY = 1.0f - 2.0f * pY / windowHeight;
}

void onMouse(int button, int state, int pX, int pY) {
  float cX = 2.0f * pX / windowWidth - 1;
  float cY = 1.0f - 2.0f * pY / windowHeight;
  std::string buttonStat;
  switch (state) {
    case GLUT_DOWN:
      buttonStat = "pressed";
      curve.PickControlPoint(cX, cY);
      break;
    case GLUT_UP:
      buttonStat = "released";
      curve.ReleaseControlPoint();
      break;
  }
  switch (button) {
    case GLUT_LEFT_BUTTON:
      printf("Left button %s at (%3.2f, %3.2f)\n", buttonStat, cX, cY);
      break;
    case GLUT_MIDDLE_BUTTON:
      printf("Middle button %s at (%3.2f, %3.2f)\n", buttonStat, cX, cY);
      break;
    case GLUT_RIGHT_BUTTON:
      printf("Right button %s at (%3.2f, %3.2f)\n", buttonStat, cX, cY);
      break;
  }
}

// Idle event indicating that some time elapsed: do animation here
void onIdle() {
  time = glutGet(GLUT_ELAPSED_TIME);
  glutPostRedisplay();  // OP will call onDisply to redraw
}
