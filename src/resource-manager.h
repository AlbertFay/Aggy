#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <map>
#include <string>

class ResourceManager {
  public:
    void LoadTexture(SDL_Renderer* renderer, std::string id, std::string filepath);
    void LoadText(SDL_Renderer*renderer, const char *id, TTF_Font *font, SDL_Color &color);
    SDL_Texture* getTexture(std::string id);
    
  private:
    std::map<std::string, SDL_Texture*> texture_map_;
};

#endif 