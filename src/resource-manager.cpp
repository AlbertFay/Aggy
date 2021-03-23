#include "resource-manager.h"

void ResourceManager::LoadTexture(SDL_Renderer* renderer, std::string id, std::string filepath){
        // Create Texture and Surfaces
    SDL_Texture* tex = NULL;
    SDL_Surface* surface = NULL;
    surface = IMG_Load(filepath.c_str());
    if (surface == NULL){
        std::cerr << "surface did not get created" << std::endl;
        std::cerr << "error = " << SDL_GetError() << std::endl;
    }
    tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (tex == NULL){
        std::cerr << "Resource-Manager::createtexture : Texture did not get created" << std::endl;
        std::cerr << "error = " << SDL_GetError() << std::endl;
    }
    // Free the surface
    SDL_FreeSurface(surface); 
    texture_map_[id] = tex;
    std::cout << "texture : " << tex << std::endl;
}

SDL_Texture* ResourceManager::getTexture(std::string id) {
    return texture_map_.at(id);
}