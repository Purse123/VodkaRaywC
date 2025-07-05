#ifndef CALAM_H_
#define CALAM_H_

#define return_defer(value) do { resultNo = value; goto defer_return;} while(0)

#include <cstdint>
#include <SDL2/SDL.h>
#include "Canvas.h"
#include <cstring>
#include <iostream>

struct vec2D { int x, y; };
struct fvec2D { float x, y; };
struct RGBA { u32 r, g, b, a; };

typedef int32_t Errno;
typedef uint8_t u8;
typedef uint32_t u32;

class Calam {
 public:
  Calam(Canvas &canvas);
  
  void putPixel (vec2D p, RGBA color);
  void putLine (vec2D p1, vec2D p2, RGBA c);
  void putLineF (fvec2D p1, fvec2D p2, RGBA c);
  void putFillRect(vec2D p1, vec2D p2, RGBA c);
  void putRect (vec2D p1, vec2D p2, RGBA c);
  void putRectF (fvec2D p1, fvec2D p2, RGBA c);
  void putTriangle (vec2D p1, vec2D p2, vec2D p3, RGBA c);
  void putFillTriangle (vec2D p1, vec2D p2, vec2D p3, RGBA c);
  void putCircle (vec2D center, int radius, RGBA c);
  void putFillCircle(vec2D center, int radius, RGBA c);
  void putFillCircleF(fvec2D center, int radius, RGBA c);
  void putEllipse (vec2D center, vec2D radius, RGBA c);
  // Errno calam_save_to_ppm (u32* frameBuffer, size_t width, size_t height);
  
 private:
  Canvas &canvas;
};
  
#endif
