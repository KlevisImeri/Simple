#ifndef OBJECT_H
#define OBJECT_H

#include "framework.h" // Include the header file for vec2 and vec4

class Object {
    unsigned int vao;   		// vertex array object id
    int nPoints;        		// number of vertices
    vec4 color;        			// color of the object
	GPUProgram& gpuProgram;		// the program

public:
    Object(std::vector<vec2>& points, vec4 color0, GPUProgram& program);

    void Draw(vec2 point, vec2 tangent, int type = GL_LINE_LOOP);
};

#endif // OBJECT_H

