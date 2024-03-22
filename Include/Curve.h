#include <iostream>

#include "GPUProgram.h"
#include "vec2.h"
using namespace std;

class Curve {
  GPUProgram *gpuProgram;

  // Vbo's Vao's
  unsigned int vaoPoints, vboPoints;
  unsigned int vaoVertices, vboVertices;

  // The Vbo's buffers
  int np;
  vec2 *points;
  int nv;
  vec2 *vertices;

  // Curect selected point
  vec2 *sp;

 public:
  Curve(GPUProgram *gpuProgram) : gpuProgram(gpuProgram) {
    np = 0;
    points = NULL;
    nv = 0;
    vertices = NULL;
    sp = NULL;
  }

  ~Curve() {
    if (points != NULL) delete points;
    if (points != NULL) delete vertices;
  }

  void Create(int np_ = 20, int nv_ = 1000) {
    np = np_;
    nv = nv_;
    points = new vec2[np];
    vertices = new vec2[nv];

    // Generate the buffers
    glGenVertexArrays(1, &vaoPoints);
    glGenBuffers(1, &vboPoints);
    glGenVertexArrays(1, &vaoVertices);
    glGenBuffers(1, &vboVertices);

    // -------------------------Points---------------------------//
    // Bind Points and work with it
    glBindVertexArray(vaoPoints);
    // Bind the buffers you need for points (here we only have one)
    glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
    // Iterate to get all the points
    double r = 0.9;
    for (int i = 0; i < np; i++) {
      double alpha = ((float)i * 2 * M_PI) / np;
      points[i] = vec2(r * cos(alpha), r * sin(alpha));
    }
    // Upload the data
    glBufferData(GL_ARRAY_BUFFER,    // vbOject!!! so you need to tell what kind
                                     // of gl obert is it
                 sizeof(vec2) * np,  // size
                 points,             // poninter to data
                 GL_DYNAMIC_DRAW);   // How to dray it
    // Enable the Vao (tell the gl where is it entry in the vertex shader)
    glEnableVertexAttribArray(0);  // Send it to the 0 location(variable)
    // You need to tell what kind of pointer youn need for the data at 0
    glVertexAttribPointer(
        0,         // which vertex attrib array it belongs to
        2,         // how many bytes is a value
        GL_FLOAT,  // what type is it
        GL_FALSE,  // should it be normalized???
        0,         // is there a stride (the distance between each other)
        NULL  // where should it start (NULL means in the begenning of array)
    );
    // -------------------------Points---------------------------//

    // ------------------------Vertices--------------------------//
    glBindVertexArray(vaoVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
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

      double t0 = s / (double)np;  // time of points 0
      double tv = i / (double)nv;  // time of vertex
      double t = (tv - t0) * np;   // tv in the hermite polynomial [0,1]

      // caculating the vectors for the hermite polynomial
      vec2 a0 = p0;
      vec2 a1 = v0;
      vec2 a2 = 3 * (p1 - p0) - (v1 + 2 * v0);
      vec2 a3 = 2 * (p0 - p1) + (v1 + v0);

      vertices[i] = a3 * (t * t * t) + a2 * (t * t) + a1 * (t) + a0;
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * nv, vertices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    // ------------------------Vertices--------------------------//
  }

  void Render() {
    glBindVertexArray(vboVertices);
    gpuProgram->setUniform(vec3(1, 0.5, 0.5), "color");
    glDrawArrays(GL_LINE_LOOP, 0, nv);

    glBindVertexArray(vboPoints);
    gpuProgram->setUniform(vec3(0.7, 0.7, 0.7), "color");
    // glPointSize(20);         // Set point size to 5
    glDrawArrays(GL_POINTS,  // how to draw
                 0,          // start
                 np          // how many
    );
  }

  void PickControlPoint(float x, float y) {
    // activate the control point that is close enough to
    // position (x,y)
  }
  void ReleaseControlPoint() {
    sp = NULL;  // there is no active control point
  }
  void MoveControlPoint(float x, float y) {
    // move the active control point if activecp is not null
    // upload the modified VBOs to the GPU
  }
};
