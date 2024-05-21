#ifndef CURVE_H
#define CURVE_H

#include "Shape.h"
using std::vector;

namespace simple {

class Curve : public Shape {
 public:
  static inline GPUProgram curveGPUProgram;

 private:
  /*----------Shaders-----------*/
  static inline const char *const vertex = R"(
    #version 330
    precision highp float;
    uniform mat4 MVP;
    layout(location = 0) in vec2 vp;
    void main() {
      gl_Position = vec4(vp.x, vp.y, 0, 1)*MVP;
    }
  )";
  static inline const char *const fragment = R"(
	  #version 330
	  precision highp float;
	  uniform vec3 color;
	  out vec4 outColor;
	  void main() {
		  outColor = vec4(color, 1);
	  }
  )";
  /*--------------------------*/

 private:
  /*---------VAO|VBO----------*/
  unsigned vaoPoints, vboPoints;
  unsigned vaoVertices, vboVertices;
  /*--------------------------*/

  /*---------Buffers----------*/
  unsigned np;
  vector<vec2> points;
  unsigned nv;
  vector<vec2> vertices;
  /*--------------------------*/

  vec2 *sp;  // Curect selected point
  vec3 colorPoint;
  vec3 colorLine;

 public:
  Curve(double r = 0.9, vec3 colorLine = {189, 116, 252},
        vec3 colorPoint = {193, 173, 204}, unsigned np = 20, unsigned nv = 1000)
      : np(np),
        nv(nv),
        sp(NULL),
        colorLine(colorLine / 255),
        colorPoint(colorPoint / 255) {
    if (!curveGPUProgram.getId()) curveGPUProgram.create(vertex, fragment, "outColor"); // id=0 mean no program there

    gpuProgram = &curveGPUProgram;

    points.resize(np);
    vertices.resize(nv);

    /* --------------------Generate Buffers-----------------------*/
    glGenVertexArrays(1, &vaoPoints);
    glGenBuffers(1, &vboPoints);
    glGenVertexArrays(1, &vaoVertices);
    glGenBuffers(1, &vboVertices);
    /* --------------------------------------------------------- */

    /* -------------------------Points---------------------------*/
    for (int i = 0; i < np; i++) {
      double alpha = ((float)i * 2 * M_PI) / np;
      points[i] = vec2(r * cos(alpha), r * sin(alpha));
    }
    upload2F(vaoPoints, 0, vboPoints, points);
    /* --------------------------------------------------------- */

    /* ------------------------Vertices--------------------------*/
    CatmullRom();
    upload2F(vaoVertices, 0, vboVertices, vertices);
    /* --------------------------------------------------------- */
  }

  void CatmullRom() {
    // ------------------------Vertices--------------------------//
    for (int i = 0; i < nv; i++) {
      double n = nv / (double)np;  // the nubmer of vertices between to points
      int s = i / n;               // the segments the point is at

      //+np so we dont get negative values (THIS ERROR GOT ME MAD)
      vec2 p_1 = points[(s + np - 1) % np];  // the point behind
      vec2 p0 = points[s + np % np];         // the p0 points
      vec2 p1 = points[(s + np + 1) % np];   // the p2 point
      vec2 p2 = points[(s + np + 2) % np];   // the p3 point

      vec2 v0 = 0.5 * (p1 - p_1);  // vec at p0
      vec2 v1 = 0.5 * (p2 - p0);   // vec at p1

      double t0 = s / (double)np;  // time of point p0
      double tv = i / (double)nv;  // time of vertex
      double t = (tv - t0) * np;   // t in the hermite polynomial [0,1]
      /**
       *
       * |-------|-------|-------|-------|-------|-------|-------|-------|
       * 0               ↑                                               1
       * 0 /np           s                                               np /np
       *
       * |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
       * 0                   ↑                                           1
       * 0 /nv               i                                           nv /nv
       *
       *             t = |-|-|          but ![0,1] range => *np
       *                 ↑   ↑
       *                 s   i
       * 0
       * |-------|-------|-------|-------|-------|-------|-------|-------|
       * |-------|-------| = t
       */

      // caculating the vectors for the hermite polynomial
      // betwen p0---p1
      vec2 a0 = p0;
      vec2 a1 = v0;
      vec2 a2 = 3 * (p1 - p0) - (v1 + 2 * v0);
      vec2 a3 = 2 * (p0 - p1) + (v1 + v0);

      vertices[i] = a3 * (t * t * t) + a2 * (t * t) + a1 * (t) + a0;
    }
  }

  void Draw() override {
    glBindVertexArray(vboVertices);
    gpuProgram->setUniform(colorLine, "color");
    glDrawArrays(GL_LINE_LOOP, 0, nv);

    glBindVertexArray(vboPoints);
    gpuProgram->setUniform(colorPoint, "color");
    // glPointSize(20);         // Set point size to 5
    glDrawArrays(GL_POINTS,  // how to draw
                 0,          // start
                 np          // how many
    );
  }

  void onKeyboard(unsigned char key, vec2 pV) override{};
  void onKeyboardUp(unsigned char key, vec2 pV) override{};

  void onMouseMotion(vec2 cP) override {
    // Update the buffers
    if (sp) {
      *sp = cP;
      upload2F(vaoPoints, 0, vboPoints, points);
      CatmullRom();
      upload2F(vaoVertices, 0, vboVertices, vertices);
    }
  }

  void onMouse(int button, int state, vec2 cP) override {
    // Redraw
    float R = 0.01;
    switch (state) {
      case GLUT_DOWN:
        // activate the control point that is close enough cP
        for (int i = 0; i < np; i++) {
          vec2 distance = cP - points[i];
          if (dot(distance, distance) < R) {
            sp = &points[i];
            break;
          }
        }
        break;
      case GLUT_UP:
        sp = NULL;
        break;
    }
  }
};

}  // namespace simple

#endif  // CURVE_H