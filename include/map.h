// TODOS:
// 1. Loading map with text file
// 2. Multiple map levels
// 3. Draw player's position (maybe FOV too)

#pragma once
#include "calam.h"
#include "Canvas.h"

#define GRIDCOLS 15
#define GRIDROWS 10

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

  void draw_npc(vec2D p, RGBA c, int radius) {
    calam.putFillCircle(p, radius, c);
  }

  // It takes p as player position
  // divide with tileSize then we get
  // position of player w.r.t grid index
  vec2D pos2index(vec2D p) {return {p.x / tileWidth, p.y / tileHeight};}
  
  // it uses pos2index
  // void def_border(vec2D p) {}

  private:
  Canvas &canvas;
  Calam &calam;
  int cols, rows;
  int tileWidth, tileHeight;
};
