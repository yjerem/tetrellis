#ifndef _shapes_h
#define _shapes_h

#include "main.h"

#define NUM_SHAPES 7
#define NUM_ROTATIONS 4
#define SHAPE_WIDTH 4
#define SHAPE_HEIGHT 4

#define TILE_WIDTH 20
#define TILE_HEIGHT 20

extern int shapes[NUM_SHAPES][NUM_ROTATIONS][SHAPE_HEIGHT][SHAPE_WIDTH];

void draw_shape(SDL_Surface * surface, int x, int y, int shape, int rot);
int real_shape_width(int shape, int rot);
int real_shape_height(int shape, int rot);
int random_shape(void);

#endif

