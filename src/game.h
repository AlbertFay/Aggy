#ifndef GAME_H
#define GAME_H

#include "controller.h"
#include "Renderer.h"
#include "SDL2/SDL.h"

class Game {
  public:
    Game(int number);
    void Run(Renderer &renderer, Controller &controller, float FPS);

  private:
  int _number;
};

#endif