#include "Simple.h"
using namespace simple;

// class SquareCurve : public Shape {
//  public:
//   SquareCurve() {
//     auto c = new Curve();
//     c->animate(Animation::ROTATING);
//     add(c);
//   }

//   void thisRender() {}
//   void onKeyboard(unsigned char key, vec2 pV){};
//   void onKeyboardUp(unsigned char key, vec2 pV){};
//   void onMouseMotion(vec2 pV){};
//   void onMouse(int button, int state, vec2 pV){};
// };

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

 public:
  TexturedQuad() {
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
    texture = new Texture(
        "D:\\Users\\Admin\\Desktop\\PROJECTS\\Simple\\Src\\brickwall.bmp");
  }

  ~TexturedQuad() { delete texture; }

  void thisRender() {
    gpuProgram->setUniform(*texture, "samplerUnit");
    glBindVertexArray(cvao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }

  void onKeyboard(unsigned char key, vec2 pV){};
  void onKeyboardUp(unsigned char key, vec2 pV){};
  void onMouseMotion(vec2 pV){
    if (sVertex) {
      *sVertex =  pV;
      upload2F(cvao, vbo[0], verteces, 0);
    }
  };
  void onMouse(int button, int state, vec2 pV) {
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
  };
};

// Instead of sence we do obejct/remove scene bcause we nned the encapsulatoin
// Or we can kep like this and do thisOnKeyborad ...

class ExScene : public Scene {
 public:
  ExScene() { add(new TexturedQuad()); }
};

int main() {
  Window win;
  win.add(new ExScene());
  win.run();

  return 0;
}
