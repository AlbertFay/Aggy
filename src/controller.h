#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL2/SDL.h"
#include "character.h"
#include "renderable.h"
#include <vector>

class Controller {
  public:
    void ChangeDirection();
    void HandleInput(Character &character, bool &running, std::vector<Renderable*> &renderables);

  private:
    const Uint8 *keystate = NULL;
};

#endif