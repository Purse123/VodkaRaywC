#include "include/map.h"
#include <iostream>
#define DELAY 9000

#define FACTOR 90
#define WIDTH (16 * FACTOR)
#define HEIGHT (9 * FACTOR)

#define PI 3.1415
#define DEG2RAD(x) (x * (PI / 180))
#define FOV DEG2RAD(60)

int main() {
  Canvas canvas(WIDTH, HEIGHT);
  Calam calam(canvas);
  GridRenderer grid(canvas, calam, GRIDCOLS, GRIDROWS);
  Player player(canvas, calam, GRIDCOLS, GRIDROWS);

  // 0 = SPACE
  // 1 = WALL
  int world_map[GRIDROWS][GRIDCOLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  };

  RGBA wallColor = {255, 255, 255, 255};
  RGBA floorColor = {30, 30, 30, 255};
  RGBA playerColor = {255, 0, 0, 255};

  // Draw only if needed (could skip rendering if allZero, or draw floor anyway)
  grid.draw_minimap(world_map, wallColor, floorColor);

  player.draw_npc({WIDTH / 2, HEIGHT / 2}, playerColor, 5);
  
  canvas.clear();
  canvas.update();
  canvas.present();

  SDL_Delay(DELAY);
  return 0;
}
