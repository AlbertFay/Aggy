#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <map>
#include <string>
#include <mutex>
#include <pthread.h>

class ResourceManager {
  public:
    std::mutex mutex_;
    void LoadTexture(SDL_Renderer* renderer, std::string id, std::string filepath);
    void LoadText(SDL_Renderer*renderer, const char *id, TTF_Font *font, SDL_Color &color);
    SDL_Texture* getTexture(std::string id);
    ResourceManager();
    ResourceManager(const ResourceManager& other);
    ResourceManager& operator=(const ResourceManager& other);
    
  private:
    std::map<std::string, SDL_Texture*> texture_map_;
};

#endif 