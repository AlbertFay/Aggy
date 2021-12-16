#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL2/SDL.h"
#include "character.h"
#include "renderable.h"
#include "renderer.h"
#include "enemy.h"
#include <vector>

class Controller {
  public:
    std::vector<std::unique_ptr<Renderable>>&& HandleInput(Character &character, bool &running, std::vector<std::unique_ptr<Renderable>> &&FiredShots, bool &pause);
    void MenuInput(bool &running, std::vector<Renderer::MenuBoxes> &boxes);
    std::vector<std::unique_ptr<Renderable>>&& EndMenuFunctions(std::vector<Renderer::MenuBoxes> &boxes, Character &character, std::vector<std::shared_ptr<Enemy>> &enemies, std::vector<std::unique_ptr<Renderable>> &&FiredShots, GameMap &map, bool &running);
    void StartMenu(bool &running, bool &startMenu, bool &allowControl);
    void PauseMenu(bool &running, bool &pause, std::vector<Renderer::MenuBoxes> &boxes);
    void PauseMenuFunctions(std::vector<Renderer::MenuBoxes> &boxes, bool &running, bool &pause);

  private:
    bool buttonRelease_ = true;
    bool leftMouseButton_ = false;
    const Uint8 *keystate = NULL;
};

#endif