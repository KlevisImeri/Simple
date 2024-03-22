#include "Triangle.h"
#include "vec3.h"

Triangle::Triangle() {
    // Constructor
}

void Triangle::bufferVertices(vec3 vertices[], const unsigned int vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * 3, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Triangle::bufferColors(vec3 colors[], const unsigned int vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * 3, colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Triangle::Create(vec3 x, vec3 y, vec3 z, vec3 c1, vec3 c2, vec3 c3) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); 

    unsigned int vbo[2];
    glGenBuffers(2, vbo);

    vec3 vertices[] = {x, y, z};
    vec3 colors[] = {c1, c2, c3};
    bufferVertices(vertices, vbo[0]);
    bufferColors(colors, vbo[1]);
}

void Triangle::Render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
