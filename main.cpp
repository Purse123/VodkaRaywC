#include "include/map.h"
#include <iostream>
#define DELAY 9000

#define FACTOR 90
#define WIDTH (16 * FACTOR)
#define HEIGHT (9 * FACTOR)

// #define FOV DEG2RAD(60)

int main() {
  Canvas canvas(WIDTH, HEIGHT);
  Calam calam(canvas);
  GridRenderer grid(canvas, calam, GRIDCOLS, GRIDROWS);
  Player player(canvas, calam, GRIDCOLS, GRIDROWS);

  RGBA wallColor = {255, 255, 255, 255};
  RGBA floorColor = {30, 30, 30, 255};
  RGBA playerColor = {255, 0, 0, 255};
  RGBA rayColor = {255, 0, 0, 255};

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

  fvec2D playerPos = {.x = WIDTH / 2, .y = HEIGHT / 2};
  u32 lastTime = SDL_GetTicks();
  bool running = true;
  bool useMouse = false;
  
  // grid.draw_minimap(world_map, wallColor, floorColor);
  while (running) {
    u32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
      if (event.type == SDL_KEYDOWN) {
	if (event.key.keysym.sym == SDLK_ESCAPE) {
	  running = false;
	}
	if (event.key.keysym.sym == SDLK_m) {
	  useMouse = !useMouse;
	  if (useMouse) {
	    SDL_ShowCursor(SDL_DISABLE);
	    SDL_SetRelativeMouseMode(SDL_TRUE);
	  } else {
	    SDL_ShowCursor(SDL_ENABLE);
	    SDL_SetRelativeMouseMode(SDL_FALSE);
	  }
	}
      }
    }
    player.npc_movement(&playerPos, deltaTime, useMouse); // movement controller
    
    canvas.clear();
    // Draw only if needed (could skip rendering if allZero, or draw floor anyway)
    grid.draw_minimap(world_map, wallColor, floorColor);

    player.npc_draw(playerPos, playerColor, 5);

    int ray_num = 64;
    // player.ray_draw(playerPos, ray_num, ray_len, rayColor);
    player.npc_drawRaysWithCollision(playerPos, ray_num, world_map, rayColor);
    
    canvas.update();
    canvas.present();
    
    // SDL_Delay(16);
  }

  SDL_Quit();
  return 0;
}
