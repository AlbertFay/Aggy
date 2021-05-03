#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class GameMap {
  public:
  
    struct Grid_Space {
      public:
        bool solid_;  
    };

    GameMap();
    void LoadMap();
    void RenderMap(SDL_Renderer* renderer);
    void Update();
    void checkCollision();

    Grid_Space array[7][7];

  private:
    int pixelsize_ = 100;
};

#endif