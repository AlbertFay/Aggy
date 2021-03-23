#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <iostream>
#include <map>
#include <string>

class ResourceManager {
  public:
    void LoadTexture(SDL_Renderer* renderer, std::string id, std::string filepath);
    SDL_Texture* getTexture(std::string id);
    
  private:
    std::map<std::string, SDL_Texture*> texture_map_;
};

#endif 