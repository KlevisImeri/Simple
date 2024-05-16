// #pragma once

// #include "Scene.h"

// namespace simple {

// class RayScene : public Scene {
//  private:
//   vector<Shape*> shapes;
//   vector<Light*> lights;
//   Camera camera{{0, 0, 2}, {0, 0, 0}, {0, 1, 0}, 45 * M_PI / 180};
//   vec3 La{0.4f, 0.4f, 0.4f};  // issue

//   public:
//     vector<vec4> render() {
//     vector<vec4> image;
//     for (int Y = 0; Y < Window::HEIGHT; Y++) {
// #pragma omp parallel forp
//       for (int X = 0; X < Window::WIDTH; X++) {
//         vec3 color = trace(camera.getRay(X, Y));
//         image[Y * Window::WIDTH + X] = vec4(color.x, color.y, color.z, 1);
//       }
//     }
//     return image;
//   }

//   Hit firstIntersect(Ray ray) {
//     Hit bestHit;
//     for (Intersectable* object : shapes) {
//       Hit hit = object->intersect(ray);  //  hit.t < 0 if no intersection
//       if (hit.t > 0 && (bestHit.t < 0 || hit.t < bestHit.t)) bestHit = hit;
//     }
//     if (dot(ray.dir, bestHit.normal) > 0)
//       bestHit.normal = bestHit.normal * (-1);
//     return bestHit;
//   }

//   bool shadowIntersect(Ray ray) {  // for directional lights
//     for (Intersectable* object : shapes)
//       if (object->intersect(ray).t > 0) return true;
//     return false;
//   }

//   const float epsilon = 0.0001f;
//   vec3 trace(Ray ray, int depth = 0) {
//     Hit hit = firstIntersect(ray);
//     if (hit.t < 0) return La;
//     vec3 outRadiance = hit.material->ka * La;
//     for (Light* light : lights) {
//       Ray shadowRay(hit.position + hit.normal * epsilon, light->direction);
//       float cosTheta = dot(hit.normal, light->direction);
//       if (cosTheta > 0 && !shadowIntersect(shadowRay)) {  // shadow computation
//         outRadiance = outRadiance + light->Le * hit.material->kd * cosTheta;
//         vec3 halfway = normalize(-ray.dir + light->direction);
//         float cosDelta = dot(hit.normal, halfway);
//         if (cosDelta > 0)
//           outRadiance =
//               outRadiance + light->Le * hit.material->ks *
//                                 powf(cosDelta, hit.material->shininess);
//       }
//     }
//     return outRadiance;
//   }
// }

// }  // namespace simple