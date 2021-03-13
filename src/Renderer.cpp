#include "renderer.h"
#include <iostream>

Renderer::Renderer(const std::size_t screen_height, const std::size_t screen_width, const std::size_t grid_height, const std::size_t grid_width)
                  :_screen_height(screen_height),
                   _screen_width(screen_width),
                   _grid_height(grid_height),
                   _grid_width(grid_width) {

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
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
Renderer::~Renderer(){
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

// Draw the objects to the window
void Renderer::Render(){
    SDL_SetRenderDrawColor(sdl_renderer, 0xcf, 0x00, 0x00, 0xFF);
    SDL_RenderClear(sdl_renderer);
    SDL_Rect block;
  block.w = _screen_width / _grid_width; 
  block.h = _screen_height / _grid_height;
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);

  SDL_RenderFillRect(sdl_renderer, &block);
  SDL_RenderPresent(sdl_renderer);
    SDL_Delay(10000);

}

// Updates the Window title to show updated score and fps
void Renderer::UpdateWindowTitle(){

}