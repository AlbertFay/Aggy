#include "Renderer.h"
#include <iostream>

Renderer::Renderer(const int screen_height, const int screen_width, const int grid_height, const int grid_width)
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
    // Initialize SDL Renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
}
Renderer::~Renderer(){
    SDL_DestroyWindow(sdl_window);
    SDL_DestroyRenderer(sdl_renderer);
}

// Draw the objects to the window
void Renderer::Render(){

}

// Updates the Window title to show updated score and fps
void Renderer::UpdateWindowTitle(){

}