#include "vec2.h"
#include "GPUProgram.h"

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
    if (points != NULL)
      delete points;
    if (points != NULL)
      delete vertices;
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
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    // Iterate to get all the points
    double r = 0.9;
    for (int i = 0; i < np; i++) {
      double alpha = ((float)i * 2 * M_PI) / np;
      points[i] = vec2(r * cos(alpha), r * sin(alpha));
    }
    // Upload the data
    glBufferData(GL_ARRAY_BUFFER, // vbOject!!! so you need to tell what kind of
                                  // gl obert is it
                 sizeof(vec2) * np, // size
                 points,            // poninter to data
                 GL_DYNAMIC_DRAW);  // How to dray it
    // Enable the Vao (tell the gl where is it entry in the vertex shader)
    glEnableVertexAttribArray(0); // Send it to the 0 location(variable)
    // You need to tell what kind of pointer youn need for the data at 0
    glVertexAttribPointer(
        0,        // which vertex attrib array it belongs to
        2,        // how many bytes is a value
        GL_FLOAT, // what type is it
        GL_FALSE, // should it be normalized???
        0,        // is there a stride (the distance between each other)
        NULL // where should it start (NULL means in the begenning of array)
    );
    // -------------------------Points---------------------------//

    // ------------------------Vertices--------------------------//
    // ------------------------Vertices--------------------------//
  }

  void Render() {
    glBindVertexArray(vboPoints);
    gpuProgram->setUniform(vec3(1, 0.5, 0.5), "color");
    // glPointSize(10.0f); // Set point size to 5

    glDrawArrays(GL_LINE_LOOP, // how to draw
                 0,            // start
                 np            // how many
    );
  }

  void PickControlPoint(float x, float y) {
    // activate the control point that is close enough to
    // position (x,y)
  }
  void ReleaseControlPoint() {
    sp = 0; // there is no active control point
  }
  void MoveControlPoint(float x, float y) {
    // move the active control point if activecp is not null
    // upload the modified VBOs to the GPU
  }
};
