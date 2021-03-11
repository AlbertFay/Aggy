#ifndef RENDERER_H
#define RENDERER_H


#include "SDL2/SDL.h"

class Renderer {
  public:

    Renderer(const int screen_height, const int screen_width, const int grid_height, const int grid_width);
    ~Renderer();

    void Render();
    void UpdateWindowTitle();

  private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    
    const int _screen_width;
    const int _screen_height;
    const int _grid_width;
    const int _grid_height;


};

#endif