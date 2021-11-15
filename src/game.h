#ifndef GAME_H
#define GAME_H

#include "controller.h"
#include "Renderer.h"
#include "SDL2/SDL.h"
#include "character.h"
#include "renderable.h"
#include "resource-manager.h"
#include "gamemap.h"
#include "collision-manager.h"
#include "ghost.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <vector>

class Game {
  public:
    ResourceManager resources_;
    Game(int number);
    void Run(Renderer &renderer, Controller &controller, float FPS, ResourceManager &resources);

  private:
  int _number;
};

#endif