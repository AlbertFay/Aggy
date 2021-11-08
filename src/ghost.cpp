#include "ghost.h"

Ghost::Ghost(){
    std::cout << "ghost has been created" << std::endl;
    //Setup starting position
    //Set angle
    //Set speed
    x_ = 300;
    y_ = 300;
    health_ = 5;
    velocity_ = 1;
};

Ghost::~Ghost(){
    std::cout << "Ghost Deconstructor called" << std::endl;
}

void Ghost::Update(){
    //I dont think I need this function but Update() is listed under renderable virtual function 
};

void Ghost::Update(int x, int y){
    //This should be the direction finding towards the characters
    int x_difference = (x - x_);
    int y_difference = (y - y_);
    double radians = atan2(y_difference, x_difference);
    angle_ = ((radians * 180)/ 3.14159) + 90; //Converted to degrees from radians
    //Update x and y with new position moving towards character
    //if moving left
    // std::cout << "collision direction X::Y  " << xCollisionDirection_ << ":" << yCollisionDirection_ << std::endl;
    if((cos(radians) * velocity_ < 0) && (xCollisionDirection_ == -1)){
        //set xoffset
        x_ = x_ - xOffset_;
        std::cout << "There is a collision on the left" << std::endl;
    }
    //If moving right
    else if((cos(radians) * velocity_) > 0 && (xCollisionDirection_ == 0)){
        //Set xOffset
        x_ = x_ - xOffset_;
        std::cout << "There is a collision on the right" << std::endl;
    }
    else {
        x_ += cos(radians) * velocity_;
        
    }
    //if moving down
    if((sin(radians) * velocity_) > 0 && (yCollisionDirection_ == -1)){
        //Set yOffset
        y_ = y_ - yOffset_;
        std::cout << "There is a collision on the bottom" << std::endl;
    }
    //if moving up
    else if((sin(radians) * velocity_) < 0 && (yCollisionDirection_ == 0)){
        //Set yOffset
        y_ = y_ - yOffset_;
        std::cout << "There is a collision on the top" << std::endl;
    }
    else {
    y_ += sin(radians) * velocity_;
    }
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
};

bool Ghost::Exists(){
    if(health_ > 0){
        return true;
    }
    else{
        return false;
    }
};