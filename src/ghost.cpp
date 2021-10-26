#include "ghost.h"

Ghost::Ghost(){
    std::cout << "ghost has been created" << std::endl;
    //Setup starting position
    //Set angle
    //Set speed
    x_ = 300;
    y_ = 300;
    health_ = 3;
};

Ghost::~Ghost(){
    std::cout << "Ghost Deconstructor called" << std::endl;
}

void Ghost::Update(){
    angle_ = 0;
    //This should be the direction finding towards the characters
    //Update x and y with new position moving towards character
};

void Ghost::RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources){
    // Create the block that is the ghost
    SDL_Rect block;
    block.w = width_;
    block.h = height_;
    block.x = x_;
    block.y = y_;
    //std::cout << "Texture: " << resources.getTexture("temp_ghost") << std::endl;
    SDL_RenderCopyEx(renderer, resources.getTexture("temp_ghost"), NULL, &block, angle_, NULL, SDL_FLIP_NONE);
    std::cout << "X:Y:Height:Width :: " << x_ << ":" << y_ << ":" << height_ << ":" << width_ << std::endl;
};

bool Ghost::Exists(){
    if(health_ > 0){
        return true;
    }
    else{
        return false;
    }
};