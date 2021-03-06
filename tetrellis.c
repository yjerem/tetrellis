#include <math.h>
#include "SDL/SDL.h"
#include "tetrellis.h"

void handle_input(Tetrellis * tetrellis) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_UP) {
          rotate_block(&tetrellis->current_block, tetrellis->field);
        } else if (event.key.keysym.sym == SDLK_LEFT) {
          move_block(&tetrellis->current_block, -1, 0, tetrellis->field);
        } else if (event.key.keysym.sym == SDLK_RIGHT) {
          move_block(&tetrellis->current_block, 1, 0, tetrellis->field);
        } else if (event.key.keysym.sym == SDLK_DOWN) {
          move_block(&tetrellis->current_block, 0, 1, tetrellis->field);
          tetrellis->last_tick = SDL_GetTicks();
        } else if (event.key.keysym.sym == SDLK_SPACE) {
          drop_block(&tetrellis->current_block, tetrellis->field);
        }
        break;

      case SDL_QUIT:
        tetrellis->quit = 1;
        break;

      default:
        break;
    }
  }
}

void update_gamestate(Tetrellis * tetrellis) {
  // move current block down by gravity, or drop a new one in if there isn't one
  if (NULL_BLOCK(tetrellis->current_block)) {
    tetrellis->current_block.shape = tetrellis->next_shape;
    tetrellis->current_block.rot = 0;
    tetrellis->current_block.x = (FIELD_WIDTH - SHAPE_WIDTH) / 2;
    tetrellis->current_block.y = real_shape_height(tetrellis->current_block.shape, tetrellis->current_block.rot) - SHAPE_HEIGHT;

    tetrellis->next_shape = random_shape();
  } else {
    if (SDL_GetTicks() - tetrellis->last_tick > tetrellis->speed) {
      move_block(&tetrellis->current_block, 0, 1, tetrellis->field);
      tetrellis->last_tick = SDL_GetTicks();
    }
  }

  // clear any lines made
  int lines;
  if (lines = clear_lines(tetrellis->field)) {
    int i;
    for (i = 0; i < lines; i++) {
      if ((tetrellis->lines_cleared + i) % LINES_NEEDED_FOR_NEXT_LEVEL == 0) {
        tetrellis->level++;
        tetrellis->speed -= INCREASE_SPEED_BY;
      }
    }

    tetrellis->lines_cleared += lines;

    printf("Level %d\n%d lines cleared\n\n", tetrellis->level, tetrellis->lines_cleared);
  }

  if (game_over(tetrellis->field)) {
    tetrellis->quit = 1;
  }
}

void render(SDL_Surface * surface, Tetrellis * tetrellis) {
  SDL_FillRect(surface, NULL, COLOR_BACKGROUND);

  draw_field(tetrellis->field, surface);
  draw_next_shape(surface, tetrellis->next_shape);

  if (! NULL_BLOCK(tetrellis->current_block)) {
    draw_shape(surface, FIELD_X + tetrellis->current_block.x * TILE_WIDTH, FIELD_Y + tetrellis->current_block.y * TILE_HEIGHT, tetrellis->current_block.shape, tetrellis->current_block.rot);
    draw_block_destination(surface, tetrellis->current_block, tetrellis->field);
  }

  SDL_UpdateRect(surface, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void game(SDL_Surface * surface) {
  Tetrellis tetrellis;
  tetrellis.field = make_field();
  tetrellis.current_block = BLOCK_NULL;
  tetrellis.next_shape = random_shape();
  tetrellis.last_tick = SDL_GetTicks();
  tetrellis.speed = INITIAL_SPEED;
  tetrellis.lines_cleared = 0;
  tetrellis.level = 1;
  tetrellis.quit = 0;

  clear_field(tetrellis.field);

  int tick = SDL_GetTicks();

  while (! tetrellis.quit) {
    handle_input(&tetrellis);
    update_gamestate(&tetrellis);
    render(surface, &tetrellis);

    // WHIRL CODE
       if (SDL_GetTicks() - tick > 100) {
         TILE_WIDTH = rand() % 5 + 15;
         TILE_HEIGHT = rand() % 5 + 15;
         tick = SDL_GetTicks();
       }

       FIELD_X = 300 + cos((float)SDL_GetTicks() / 500.0f) * 150.0;
       FIELD_Y = 150 + sin((float)SDL_GetTicks() / 500.0f) * 150.0;
    // THAT'S IT

    SDL_Delay(1);
  }

  destroy_field(tetrellis.field);
}

