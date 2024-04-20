// #include "Simple.h"

// GPUProgram gpuProgram;

// // The virtual world: collection of two objects
// Object *vehicle; // moving object
// Object *path;    // the path of the moving object

// // Path of the object and the derivative with Clifford algebra
// // It gives the values of derivative and f at time tt
// void Path(float tt, Dnum &x, Dnum &y) {
//   Dnum t(tt, 1);
//   x = Sin(t) * (Sin(t) + 3) * 0.4 / (Tan(Cos(t)) + 2);
//   y = (Cos(Sin(t) * 8 + 1) * 1.2 + 0.2) / (Pow(Sin(t) * Sin(t), 3) + 2);
// }

// // Initialization, create an OpenGL context
// void onInitialization() {
//   glViewport(0, 0, windowWidth, windowHeight);
//   glLineWidth(3);

//   // vehicle
//   std::vector<vec2> vehiclePoints{vec2(0.1, 0), vec2(-0.1, -0.1), vec2(0, 0),
//                                   vec2(-0.1, 0.1)};
//   vec4 color = vec4(1, 1, 0, 1);
//   vehicle = new Object(vehiclePoints, color, gpuProgram);

//   // path
//   std::vector<vec2> pathPoints;
//   for (float t = 0; t < 2.0f * M_PI; t += 0.01f) {
//     Dnum x, y;
//     Path(t, x, y);
//     pathPoints.push_back(vec2(x.value, y.value)); // store function
//     // values as path
//   }
//   color = vec4(0, 0, 1, 1);
//   path = new Object(pathPoints, color, gpuProgram);

//   // create program for the GPU
//   gpuProgram.create(vertexDnum, fragmentDnum, "fragmentColor");
// }

// // Window has become invalid: Redraw
// void onDisplay() {
//   glClearColor(0.8, 0.8, 0.8, 1);                     // background color
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //
//   // clear the screen
//   // Draw path
//   path->Draw(vec2(0, 0), vec2(1, 0));

//   // Animate and draw vehicle
//   long time = glutGet(GLUT_ELAPSED_TIME); // elapsed time since the start of the
//   float sec = time / 1000.0f;     // convert msec to sec
//                                           // Compute tangent with derivation
//   Dnum x, y;
//   Path(sec / 2, x, y);
//   vec2 position(x.value, y.value);
//   vec2 velocity(x.derivative, y.derivative);
//   float speed = length(velocity); // velocity
//   vec2 heading = velocity / speed;
//   // Draw with transformation
//   vehicle->Draw(position, heading, GL_TRIANGLE_FAN);
//   glutSwapBuffers();
//   // exchange the two buffers
// }

// // Key of ASCII code pressed
// void onKeyboard(unsigned char key, int pX, int pY) {}
// // Key of ASCII code released
// void onKeyboardUp(unsigned char key, int pX, int pY) {}
// // Mouse click event
// void onMouse(int button, int state, int pX, int pY) {}
// // Move mouse with key pressed
// void onMouseMotion(int pX, int pY) {}

// // Idle event indicating that some time elapsed: do animation here
// void onIdle() {
//   glutPostRedisplay(); // redraw the scene
// }
