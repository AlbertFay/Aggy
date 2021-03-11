#include "Renderer.h"
#include <iostream>

class Renderer{
    Renderer(const int screen_height, const int screen_width, const int grid_height, const int grid_width){
        if(SDL_Init(SDL_INIT_VIDEO) < 0){
            std::cout << "SDL_INIT_VIDEO failed to initialize" << std::endl;
        }
    }
};