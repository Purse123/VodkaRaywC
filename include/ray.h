#pragma once
#include "calam.h"
#include "Canvas.h"

int resolution = 4;
int num_ray = window_width / resolution;

Class Ray {
  vec2D x, y;
  public:
  Ray(vec2D a, vec2D b): x(a), y(b) {}
  
  void Draw() {
  }
}
