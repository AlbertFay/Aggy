#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "renderable.h"
#include "character.h"
#include "gamemap.h"
#include "shotfired.h"
#include "enemy.h"

class CollisionManager{
  public:
    CollisionManager();
    void CheckCollisions(Character &character, GameMap &map); //Implemented
    void CheckCollisions(std::vector<Renderable*> &renderables, GameMap &map); //Implemented
    
    void CheckCollisions(std::vector<Enemy*> &enemies, GameMap &map); //Implemented
    void CheckCollisions(std::vector<Enemy*> &enemies, std::vector<Renderable*> &renderables); //Implemented
    void CheckCollisions(std::vector<Enemy*> &enemies, Character &character); //Implemented
    void LoadResources(SDL_Renderer *renderer, ResourceManager &resources);

  private:
};

#endif