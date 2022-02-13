#include <SDL2/SDL.h>
#include <common.h>
#include <universe.h>

#include <iostream>

// function `log` and SDL usage were modified from 
// Tyler Brock's implementation of 
// Conway's Game of Life which is published under MIT license: 
// https://github.com/TylerBrock/game-of-life

inline void log(const std::string& msg) {
  std::cout << "[  GAME  ] " << msg << std::endl;
}

int main() {
  log("initializing...");

  SDL_Window* window;
  SDL_Renderer* renderer;

  SDL_Init(SDL_INIT_VIDEO);

  log("creating window...");
  window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WIDTH * SCALE,
                            HEIGHT * SCALE, SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    log("cannot create window.\n SDL_Error: " + std::string(SDL_GetError()));
    return 1;
  }

  log("creating renderer...");
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_RenderClear(renderer);

  log("creating texture...");
  SDL_Texture* texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

  Universe universe(HEIGHT, WIDTH);
  SDL_UpdateTexture(texture, NULL, universe.output(ON_COLOR, OFF_COLOR).get(),
                    WIDTH * sizeof(uint32_t));

  bool quit = false;
  bool drawing = false;

  SDL_Event event;
  cells_output_t cells_output;
  Cell c;

  while (!quit) {
    SDL_WaitEvent(&event);

    switch (event.type) {
      case SDL_MOUSEBUTTONDOWN:
        c = universe.get_cell(event.button.y / SCALE, event.button.x / SCALE);
        if (c == Alive) {
          universe.set_cell(event.button.y / SCALE, event.button.x / SCALE,
                            Dead);
        } else {
          universe.set_cell(event.button.y / SCALE, event.button.x / SCALE,
                            Alive);
        }
        drawing = true;
        break;
      case SDL_MOUSEMOTION:
        if (event.motion.state & SDL_BUTTON(1)) {
          c = universe.get_cell(event.button.y / SCALE, event.button.x / SCALE);
          if (c == Alive) {
            universe.set_cell(event.button.y / SCALE, event.button.x / SCALE,
                              Dead);
          } else {
            universe.set_cell(event.button.y / SCALE, event.button.x / SCALE,
                              Alive);
          }
          drawing = true;
        }
        break;
      case SDL_MOUSEBUTTONUP:
        drawing = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_SPACE) {
          log("evolving to next generation...");
          universe.evolve();
        }
        drawing = true;
        break;
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYUP:
        drawing = false;
        break;
      default:
        break;
    }
    if (drawing && !quit) {
      SDL_UpdateTexture(texture, NULL,
                        universe.output(ON_COLOR, OFF_COLOR).get(),
                        WIDTH * sizeof(uint32_t));
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
      drawing = false;
    }
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
