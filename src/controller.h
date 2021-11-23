#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL2/SDL.h"
#include "character.h"
#include "renderable.h"
#include <vector>

class Controller {
  public:
    void ChangeDirection();
    void HandleInput(Character &character, bool &running);
    void MenuInput(bool &running);

  private:
    bool buttonRelease_ = true;
    bool leftMouseButton_ = false;
    const Uint8 *keystate = NULL;
    //SDL_MouseButtonEvent mousestate;
};

#endif