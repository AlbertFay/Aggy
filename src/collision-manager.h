#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "renderable.h"
#include "character.h"
#include "gamemap.h"
#include "shotfired.h"
#include "enemy.h"
#include "renderer.h"

#include <vector> 

class CollisionManager{
  public:
    CollisionManager();
    void CheckCollisions(Character &character, GameMap &map); //Implemented
    std::vector<std::unique_ptr<Renderable>>&& CheckCollisions(std::vector<std::unique_ptr<Renderable>> &&FiredShots, GameMap &map); //Implemented
    void CheckCollisions(std::vector<std::shared_ptr<Enemy>> &enemies, GameMap &map); //Implemented
    std::vector<std::unique_ptr<Renderable>>&& CheckCollisions(std::vector<std::shared_ptr<Enemy>> &enemies, std::vector<std::unique_ptr<Renderable>> &&FiredShots); //Implemented
    void CheckCollisions(std::vector<std::shared_ptr<Enemy>> &enemies, Character &character); //Implemented
    void CheckCollisions(std::vector<Renderer::MenuBoxes> &boxes);
    void LoadResources(SDL_Renderer *renderer, ResourceManager &resources);

  private:
};

#endif