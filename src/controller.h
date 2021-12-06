#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL2/SDL.h"
#include "character.h"
#include "renderable.h"
#include <vector>

class Controller {
  public:
    void ChangeDirection();
    std::vector<std::unique_ptr<Renderable>>&& HandleInput(Character &character, bool &running, std::vector<std::unique_ptr<Renderable>> &&FiredShots);
    void MenuInput(bool &running);

  private:
    bool buttonRelease_ = true;
    bool leftMouseButton_ = false;
    const Uint8 *keystate = NULL;
    //SDL_MouseButtonEvent mousestate;
};

#endif