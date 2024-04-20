#ifndef HELPERFUNCTOIN_H
#define HELPERFUNCTOIN_H

#include "Window.h"
#include "vec2.h"

namespace simple {
/**
 * This is a header file composd of functions which done belong
 * logically to a specific class but they are helpful during
 * implmentatoin => helper functions.
 */

/**
 * float cX = 2.0f * pX / windowWidth - 1;
 * float cY = 1.0f - 2.0f * pY / windowHeight;
 *
 *
 *        PIXELS              SQUISH 0,1 => STREACH BY 2       CENTER WITH -1
 * windowHeight
 *
 *
 *                                                                          ↑ 1
 *                                                                [ | | | | | |
 * | | | ] [ | | | | | | | | | ] [ | | | | | | | | | ] 0        1         2 0 1
 * 2     ↖       [ | | | | | | | | | ]
 *  |--------|--------->   ==>   |--------|--------->    ==>
 * <----------|-----------> | [ | | ]                    | [ | | | | | | | ] -1
 * [ | | | | | | | | | ] 1 | [ | | ]                    | [ | | | | | | | ] [ |
 * | | | | | | | | ] 1| [ | | ]                   1| [ | | | | | | | ] [ | | | |
 * | | | | | ] ↓                            | [ | | | | | | | ]              [ |
 * | | | | | | | | ] | [ | | | | | | | ]                        ↓ -1 2↓ [ | | |
 * | | | | ]
 *
 *
 * You make the interval [ 0, 1]
 * You streach to        [ 0, 2]
 * Then you center to    [-1,-1]
 *
 * cX you have to shift left by 1 => -1
 * cy you have to shift up   by 1 => +1
 *
 */
// vec2 Viewport2Window(vec2 pixel) {  // This should be put under transformations
//   return {2.0f * pixel.x / Window::WIDTH - 1,
//           1.0f - 2.0f * pixel.y / Window::HEIGHT};
// }

}  // namespace simple
#endif  // HELPERFUNCTOIN_H