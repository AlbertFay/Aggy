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

  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    std::cout << "IMG_Init did not initialize" << std:: endl;
    std::cout << "Error code: " << IMG_GetError();
  }

  // Initialize SDL Window
  sdl_window = SDL_CreateWindow("Aggy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_height, _screen_width, SDL_WINDOW_SHOWN);
  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  std::cout << "SDL is initialized" << "\n";

  // Initialize SDL Renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

}
Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyRenderer(sdl_renderer);
  
  IMG_Quit();
  SDL_Quit();
}

// Draw the objects to the window
void Renderer::Render(Character &character, std::vector<Renderable*> renderables) {

  // Clear the Render and change color of background
  SDL_SetRenderDrawColor(sdl_renderer, 90, 90, 90, 255);
  SDL_RenderClear(sdl_renderer);

  //Render the character
  character.Render(sdl_renderer);

  for (auto renderable: renderables) {
    renderable->RenderRenderable(sdl_renderer);
  }
  

  // Display the Render onto the screen; Update Frame
  SDL_RenderPresent(sdl_renderer);

}


SDL_Renderer* Renderer::GetRenderer() {
  return sdl_renderer;
}

// Updates the Window title to show updated score and fps
void Renderer::UpdateWindowTitle() {
}