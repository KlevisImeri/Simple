#pragma once
#include "Shape.h"
using std::vector;
namespace simple {

class TexturedQuad : public Shape {
 public:
  static inline GPUProgram textureQuadGPUprogram;
  static inline const char* const vertex = R"(
    #version 330 
    precision highp float; 
    uniform mat4 MVP; 
    layout(location = 0) in vec2 vp; 
    layout(location = 1) in vec2 vt; 
    out vec2 texcoord; 
    void main() { 
      gl_Position = vec4(vp.x, vp.y, 0, 1) * MVP; 
      texcoord = vt; 
    }
  )";
  static inline const char* const fragment = R"(
    #version 330 
    precision highp float; 
    uniform sampler2D samplerUnit; 
    in vec2 texcoord; 
    out vec4 outColor; 
    void main() { 
      outColor = texture(samplerUnit, texcoord); 
    }
  )";

 private:
  unsigned int cvao, vbo[2];
  Texture* texture;
  vector<vec2> verteces = {{-0.5, -0.5}, {0.5, -0.5}, {-0.5, 0.5}, {0.5, 0.5}};
  vec2* sVertex;  // selected vertex

  void initialize() {
    if (!textureQuadGPUprogram.getId()) {
      textureQuadGPUprogram.create(vertex, fragment, "outColor");
    }
    glGenVertexArrays(1, &cvao);
    glGenBuffers(2, vbo);
    gpuProgram = &textureQuadGPUprogram;
    vector<vec2> textureCordinates = {
        {0.0, 0.0}, {4.0, 0.0}, {0.0, 4.0}, {4.0, 4.0}};
    upload2F(cvao, vbo[0], verteces, 0);
    upload2F(cvao, vbo[1], textureCordinates, 1);
  }

 public:
  TexturedQuad(string path) {
    initialize();
    texture = new Texture(path);
  }

  TexturedQuad(vector<vec4> image) {
    initialize();
    texture = new Texture(Window::WIDTH, Window::HEIGHT, image);
  }


  ~TexturedQuad() { delete texture; }

  void Draw() override {
    gpuProgram->setUniform(*texture, "samplerUnit");
    glBindVertexArray(cvao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }

  void onMouseMotion(vec2 pV) override {
    if (sVertex) {
      *sVertex = pV;
      upload2F(cvao, vbo[0], verteces, 0);
    }
  };

  void onMouse(int button, int state, vec2 pV) override {
    float R = 0.01;
    switch (state) {
      case GLUT_DOWN:
        for (int i = 0; i < verteces.size(); i++) {
          vec2 distance = pV - verteces[i];
          if (dot(distance, distance) < R) {
            sVertex = &verteces[i];
            break;
          }
        }
        break;
      case GLUT_UP:
        sVertex = NULL;
        break;
    }
  }
};

}  // namespace simple
