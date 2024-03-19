#include "Simple.h"
using namespace std;
// global variables
GPUProgram gpuProgram; // vertex and fragment shaders
long time = 0;         // time for animation rendering

// Class Curve
class Curve {
  unsigned int vaoPoints, vboPoints;
  unsigned int vaoVertices, vboVertices;
  int npoints;    // number of control points
  vec2 *points;   // array for the control points
  int nvertices;  // number of vertices for the polyline
  vec2 *vertices; // array for the vertices
  vec2 *activecp; // address of the moving control point

  vec2 CurvePoint(float t) {
    if (points) {
      float tt = t * npoints;
      int i1 = (int)floor(tt);
      float tau = tt - i1;
      int i0 = (i1 + npoints - 1) % npoints;
      int i2 = (i1 + 1) % npoints;
      int i3 = (i1 + 2) % npoints;
      i1 = i1 % npoints;
    }

    return vec2(0, 0);
  }

public:
  Curve() {
    points = 0;
    npoints = 0;
    vertices = 0;
    nvertices = 0;
    activecp = 0;
  }

  ~Curve() {
    if (points != 0)
      delete points;
    if (vertices != 0)
      delete vertices;
  }

  void Create(int np = 20, int nv = 1000) {
    npoints = np;
    nvertices = nv;
    glGenVertexArrays(1, &vaoPoints);
    glBindBuffer(GL_ARRAY_BUFFER, vaoPoints);
    glGenBuffers(1, &vboPoints);
    glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
    points = new vec2(npoints);
    for (int i = 0; i < npoints; i++) {
      float alpha = 2.0 * M_PI * (float)i / npoints; // angle
      points[i] = vec2(0.9 * cos(alpha), 0.9 * sin(alpha));
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * npoints, points,
                 GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glGenVertexArrays(1, &vaoVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vaoVertices);
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    vertices = new vec2(npoints);
    for (int i = 0; i < nvertices; i++) {
      float t = (float)t / (nvertices - 1);
      vertices[i] = CurvePoint(t);
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * nvertices, points,
                 GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
  }

  void Render() {
    // activate VAOs and render the curve together with the control points
    glBindVertexArray(vaoVertices);
    gpuProgram.setUniform(vec3(1, 1, 0), "color");
    glDrawArrays(GL_LINE_STRIP, 0, nvertices);

    glBindVertexArray(vaoPoints);
    gpuProgram.setUniform(vec3(1, 1, 0), "color");
    glDrawArrays(GL_POINTS, 0, npoints);
  }

  void PickControlPoint(float x, float y) {
    float epsilon = 0.05;
    for (int i = 0; i < npoints; i++) {
      float dx = x - points[i].x;
      float dy = y - points[i].y;
    }
  }

  void ReleaseControlPoint() { activecp = 0; }

  void OnMouseCliced(int x, int y) {

    for (int i = 0; i < nvertices; i++) {
      float t = (float)t / (nvertices - 1);
      vertices[i] = CurvePoint(t);
    }
  }
};

Curve curve;

// Initialization, create an OpenGL context
void onInitialization() {
  glViewport(0, 0, windowWidth, windowHeight);
  curve.Create();
  gpuProgram.create(vertexMVP, fragmentDefault, "outColor");
}

// Window has become invalid: Redraw
void onDisplay() {
  glClearColor(0, 0, 0, 0);     // background color
  glClear(GL_COLOR_BUFFER_BIT); // clear frame buffer

  curve.Render();

  mat4 MVP = ScaleMatrix(vec3(1, 1, 1));
  gpuProgram.setUniform(MVP, "MVP");
  glutSwapBuffers(); // exchange buffers for double buffering
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
  char *buttonStat;
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
  glutPostRedisplay(); // OP will call onDisply to redraw
}
