#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL2/SDL.h"
#include "character.h"

class Controller {
  public:
    void ChangeDirection();
    void HandleInput(Character &character, bool &running);

  private:
    const Uint8 *keystate = NULL;
};

#endif