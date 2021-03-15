#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL2/SDL.h"

class Controller {
  public:
    void ChangeDirection();
    void HandleInput(bool &running);
};

#endif