#include "resource-manager.h"



void ResourceManager::LoadTexture(SDL_Renderer* renderer, std::string id, std::string filepath){
    mutex_.lock();

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
    mutex_.unlock();
    std::cout << "\"" << id << "\" has been put into texture map" << std::endl; 
    
}

void ResourceManager::LoadText(SDL_Renderer*renderer, const char *id, TTF_Font *font, SDL_Color &color){
    mutex_.lock();
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, id, color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    std::string stringID = id;
    texture_map_[stringID] = Message;
    mutex_.unlock();
    std::cout << "\"" << id << "\" has been put into texture map" << std::endl; 
};

SDL_Texture* ResourceManager::getTexture(std::string id) {
    mutex_.lock();
    if(texture_map_.count(id)){
        //std::cout << "Texture ID \"" << id << "\" is found in resources" << std::endl;
        mutex_.unlock();
        return texture_map_.at(id);
    }
    else {
        std::cerr << "Texture ID \"" << id << "\" is not found in resources" << std::endl;
        mutex_.unlock();
        return NULL;
    }
};
ResourceManager::ResourceManager(){
    //Constructor
};
ResourceManager::ResourceManager(const ResourceManager& other) : texture_map_(other.texture_map_){
};

ResourceManager& ResourceManager::operator=(const ResourceManager& other){
    texture_map_ = other.texture_map_;
    return *this;
};