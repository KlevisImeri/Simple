// #ifndef OBJECT_H
// #define OBJECT_H

// #include "GPUProgram.h"
// #include "vec4.h"
// #include "vec2.h"

// namespace simple {

// class Object {
//   unsigned int vao;        // vertex array object id
//   int nPoints;             // number of vertices
//   vec4 color;              // color of the object
//   GPUProgram& gpuProgram;  // the program

//  public:
//   Object(std::vector<vec2>& points, vec4 color0, GPUProgram& program) {
//     color = color0;
//     nPoints = points.size();

//     glGenVertexArrays(1, &vao);          // create 1 vertex array object
//     glBindVertexArray(vao);              // make it active
//     unsigned int vbo;                    // vertex buffer objects
//     glGenBuffers(1, &vbo);               // Generate 1 vertex buffer objects
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);  // mate this vbo active

//     glBufferData(GL_ARRAY_BUFFER,               // copy to the GPU
//                  points.size() * sizeof(vec2),  // size of data in bytes
//                  &points[0],       // address of the data array on the CPU
//                  GL_STATIC_DRAW);  // copy to GPU

//     glEnableVertexAttribArray(0);
//     // Data organization of Attribute Array 0
//     glVertexAttribPointer(
//         0,            // Attribute Array 0
//         2, GL_FLOAT,  // components/attribute, component type
//         GL_FALSE,     // not in fixed point format, do not normalized
//         0, NULL);     // stride and offset: it is tightly packed
//   }

//   void Draw(vec2 point, vec2 tangent, int type) {
//     gpuProgram.setUniform(point, "point");  // set uniform parameters
//     gpuProgram.setUniform(tangent, "tangent");
//     gpuProgram.setUniform(color, "color");

//     glBindVertexArray(vao);  // make the vao and its vbos active playing the
//                              // role of the data source
//     glDrawArrays(
//         type, 0,
//         nPoints);  // draw a single line loop with vertices defined in vao
//   }
// };

// }  // namespace simple

// #endif  // OBJECT_H
