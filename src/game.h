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
#include "level.h"

#include <future>
#include <iostream>
#include <vector>
#include <chrono>

class Game {
  public:
  
  //Timer using RAII to determine how long a program runs until
  //it reaches end of scope
  struct Timer{
    public:
      Timer(){};
      ~Timer(){
        end_ = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(start_).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(end_).time_since_epoch().count();

        auto duration = end - start;
        std::cout << "Time elapsed : (" << duration << " nanoseconds)" << std::endl;
      };
    private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_ = std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::high_resolution_clock> end_ = std::chrono::high_resolution_clock::now();

  };
    Game();
    void Run(Renderer &renderer, Controller &controller, float FPS, ResourceManager &resources);

  private:
};

#endif