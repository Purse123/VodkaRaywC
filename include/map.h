// TODOS:
// 1. Loading map with text file
// 2. Multiple map levels
// 3. Draw player's position (maybe FOV too)

#pragma once
#include <cmath>
#include "calam.h"
#include "Canvas.h"

#define GRIDCOLS 15
#define GRIDROWS 10

#define PI 3.1415
#define DEG2RAD(x) (x * (PI / 180))

class GridRenderer {
 public:
  GridRenderer(Canvas &canvas, Calam &calam, int gridCols, int gridRows):
    canvas(canvas), calam(calam), cols(gridCols), rows(gridRows) {
    tileWidth = canvas.getWidth() / cols;
    tileHeight = canvas.getHeight() / rows;
  }

  void draw_minimap (int world[GRIDROWS][GRIDCOLS], RGBA wallColor, RGBA floorColor) {
    for (int row = 0; row <= GRIDROWS; ++row) {
      for (int col = 0; col <= GRIDCOLS; ++col) {
	int value = world[row][col];
	RGBA color = (value == 1) ? wallColor : floorColor;

	int x = col * tileWidth;
	int y = row * tileHeight;

	int w = canvas.getWidth();
	int h = canvas.getHeight();
	
	calam.putRect({x - 1, y - 1}, {w - 1, h - 1}, {0, 0, 0, 255}); // outline
	calam.putFillRect({x, y}, {w, h}, color);
      }
    }
  }
    
private:
  Canvas &canvas;
  Calam &calam;
  int cols, rows;
  int tileWidth, tileHeight;
};

class Player {
  public:
  Player(Canvas &canvas, Calam &calam, int gridCols, int gridRows):
    canvas(canvas), calam(calam), cols(gridCols), rows(gridRows) {
    tileWidth = canvas.getWidth() / cols;
    tileHeight = canvas.getHeight() / rows;
  }

  void npc_draw(fvec2D p, RGBA c, int radius) {
    calam.putFillCircleF(p, radius, c);
  }

  void npc_movement(fvec2D* playerPos, float dt, bool useMouse) {
    if (useMouse) {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      playerPos->x = static_cast<float>(mouseX);
      playerPos->y = static_cast<float>(mouseY);
    } else {
      const u8 *key = SDL_GetKeyboardState(NULL);
      // smooth deltaTime
      float adjSpeed = speed * dt;
    
      if (key[SDL_SCANCODE_W]) playerPos->y -= adjSpeed;
      if (key[SDL_SCANCODE_S]) playerPos->y += adjSpeed;
      if (key[SDL_SCANCODE_A]) playerPos->x -= adjSpeed;
      if (key[SDL_SCANCODE_D]) playerPos->x += adjSpeed;
    }
    if (playerPos->x < 0) playerPos->x = 0;
    if (playerPos->y < 0) playerPos->y = 0;
    if (playerPos->x > canvas.getWidth()) playerPos->x = canvas.getWidth();
    if (playerPos->y > canvas.getHeight()) playerPos->y = canvas.getHeight();
  }

  // It takes p as player position
  // divide with tileSize then we get
  // position of player w.r.t grid index
  // vec2D pos2index(vec2D p) {return {p.x / tileWidth, p.y / tileHeight};}

  void ray_draw(fvec2D p, int num, float len, RGBA c) {
    float angleStep = 360.0f / num;
    for (int i = 0; i < num; ++i) {
      float angle = i * angleStep;

      fvec2D rayEnd;
      rayEnd.x = p.x + len * cos(DEG2RAD(angle));
      rayEnd.y = p.y + len * sin(DEG2RAD(angle));
      calam.putLineF(p, rayEnd, c);
    }
  }
  void npc_drawRaysWithCollision(fvec2D playerPos, int numRays, int world[GRIDROWS][GRIDCOLS], RGBA rayColor) {
    float angleStep = 360.0f / numRays;
    for (int i = 0; i < numRays; ++i) {
        float angle = i * angleStep;
	
        float dx = cos(DEG2RAD(angle));
        float dy = sin(DEG2RAD(angle));

        fvec2D rayPos = playerPos;
        float stepSize = 1.0f;

	while (true) {
	  rayPos.x += dx * stepSize;
	  rayPos.y += dy * stepSize;
	  
	  int mapX = (int)(rayPos.x) / tileWidth;
	  int mapY = (int)(rayPos.y) / tileHeight;

	  if (mapX < 0 || mapY < 0 || mapX >= GRIDCOLS || mapY >= GRIDROWS) {
	    break;  // Out of bounds
	  }
	  if (world[mapY][mapX] == 1) {
	    break;  // Hit wall
	  }
        }
        calam.putLineF(playerPos, rayPos, rayColor);
    }
  }
  
  private:
  Canvas &canvas;
  Calam &calam;
  int cols, rows;
  int tileWidth, tileHeight;
  static float speed;
};

float Player::speed = 30.0f;
