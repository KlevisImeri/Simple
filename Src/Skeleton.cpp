#include "framework.h"
#include "fragmentShader.h"
#include "vertexShader.h"
#include "Triangle.h"
// global variables
GPUProgram gpuProgram;  // vertex and fragment shaders
long time = 0;          // time for animation rendering


Triangle triangle;

// Initialization, create an OpenGL context
void onInitialization() {
  //glViewport(0, 0, windowWidth, windowHeight); //Why we need this
  triangle.Create();
  gpuProgram.create(vertexMVP, fragmentDefault, "outColor");
}

// Window has become invalid: Redraw
void onDisplay() {
  glClearColor(0, 0, 0, 0);      // background color
  glClear(GL_COLOR_BUFFER_BIT);  // clear frame buffer

  // mat4 MVP = TranslateMatrix(vec3(sin(time / 1000.0), 0.0, 0.0)) *
  //            ScaleMatrix(vec3(0.5, 0.5, 0.5)) *
  //            RotationMatrix(time / (M_PI * 1000), vec3(0.0, 0.0, 1.0));
  mat4 MVP = ScaleMatrix(vec3(1, 1, 1));
  gpuProgram.setUniform(MVP, "MVP");

  triangle.Render();

  glutSwapBuffers();  // exchange buffers for double buffering
}

// Key of ASCII code pressed
void onKeyboard(unsigned char key, int pX, int pY) {
  if (key == 'd') glutPostRedisplay();  // if d, invalidate display, i.e. redraw
}

// Key of ASCII code released
void onKeyboardUp(unsigned char key, int pX, int pY) {}

// Move mouse with key pressed
void onMouseMotion(
    int pX, int pY) {  // pX, pY are the pixel coordinates of the cursor in the
                       // coordinate system of the operation system
  // Convert to normalized device space
  float cX = 2.0f * pX / windowWidth - 1;  // flip y axis
  float cY = 1.0f - 2.0f * pY / windowHeight;
  printf("Mouse moved to (%3.2f, %3.2f)\n", cX, cY);
}

// Mouse click event
void onMouse(int button, int state, int pX,
             int pY) {  // pX, pY are the pixel coordinates of the cursor in the
                        // coordinate system of the operation system
  // Convert to normalized device space
  float cX = 2.0f * pX / windowWidth - 1;  // flip y axis
  float cY = 1.0f - 2.0f * pY / windowHeight;

  char* buttonStat;
  switch (state) {
    case GLUT_DOWN:
      buttonStat = "pressed";
      break;
    case GLUT_UP:
      buttonStat = "released";
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
