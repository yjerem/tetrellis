#include "SDL/SDL.h"
#include "shapes.h"

int shapes[NUM_SHAPES][NUM_ROTATIONS][SHAPE_HEIGHT][SHAPE_WIDTH] = {
  // I
  {
    {
      { 1,0,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,1,1 }
    },
    {
      { 1,0,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,1,1 }
    }
  },

  // J
  {
    {
      { 0,0,0,0 },
      { 0,1,0,0 },
      { 0,1,0,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,0,0,0 },
      { 1,1,1,0 }
    },
    {
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,1,0 },
      { 0,0,1,0 }
    }
  },

  // L
  {
    {
      { 0,0,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,1,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 0,1,0,0 },
      { 0,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,0,1,0 },
      { 1,1,1,0 }
    }
  },

  // S
  {
    {
      { 0,0,0,0 },
      { 1,0,0,0 },
      { 1,1,0,0 },
      { 0,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,1,1,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 1,0,0,0 },
      { 1,1,0,0 },
      { 0,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,1,1,0 },
      { 1,1,0,0 }
    }
  },

  // Z
  {
    {
      { 0,0,0,0 },
      { 0,1,0,0 },
      { 1,1,0,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 0,1,1,0 }
    },
    {
      { 0,0,0,0 },
      { 0,1,0,0 },
      { 1,1,0,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 0,1,1,0 }
    }
  },

  // T
  {
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,1,0 },
      { 0,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,1,0,0 },
      { 1,1,0,0 },
      { 0,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,1,0,0 },
      { 1,1,1,0 }
    },
    {
      { 0,0,0,0 },
      { 1,0,0,0 },
      { 1,1,0,0 },
      { 1,0,0,0 }
    }
  },

  // O
  {
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 1,1,0,0 }
    }
  }
};

void draw_shape(SDL_Surface * surface, int x, int y, int shape, int rot) {
  int tile_x, tile_y;

  SDL_Rect tile;
  tile.w = TILE_WIDTH;
  tile.h = TILE_HEIGHT;

  for (tile_x = 0; tile_x < SHAPE_WIDTH; tile_x++) {
    for (tile_y = 0; tile_y < SHAPE_HEIGHT; tile_y++) {
      if (shapes[shape][rot][tile_y][tile_x] == 1) {
        tile.x = x + tile_x * TILE_WIDTH;
        tile.y = y + tile_y * TILE_HEIGHT;
        SDL_FillRect(surface, &tile, shape * 5 + 5);
      }
    }
  }
}

