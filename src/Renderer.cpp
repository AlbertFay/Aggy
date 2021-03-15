#include "renderer.h"
#include <iostream>

Renderer::Renderer(const std::size_t screen_height, const std::size_t screen_width, const std::size_t grid_height, const std::size_t grid_width)
    : _screen_height(screen_height),
      _screen_width(screen_width),
      _grid_height(grid_height),
      _grid_width(grid_width) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL_INIT_VIDEO failed to initialize" << std::endl;
  }
  // Initialize SDL Window
  sdl_window = SDL_CreateWindow("Aggy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_height, _screen_width, SDL_WINDOW_SHOWN);
  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize SDL Renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}
Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

// Draw the objects to the window
void Renderer::Render(Character const character) {
  //Render Character
  SDL_Rect block;
  block.w = 20;
  block.h = 20;
  block.x = 100;
  block.y = 100;

  SDL_SetRenderDrawColor(sdl_renderer, 90, 90, 90, 255);
  SDL_RenderClear(sdl_renderer);

  SDL_SetRenderDrawColor(sdl_renderer, 70, 215, 50, 255);
  SDL_RenderFillRect(sdl_renderer, &block);
  SDL_RenderPresent(sdl_renderer);


  //To be dealt with later.
  //SDL_RenderCopyEx(sdl_renderer, sdl)

  //SDL_Delay(10000);
}

// Updates the Window title to show updated score and fps
void Renderer::UpdateWindowTitle() {
}