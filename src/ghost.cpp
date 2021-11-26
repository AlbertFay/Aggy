#include "ghost.h"

Ghost::Ghost(){
    //std::cout << "ghost has been created" << std::endl;
    //Setup starting position
    //Set angle
    //Set speed
    x_ = 300;
    y_ = 300;
    health_ = 5;
    velocity_ = 1;
    LoadAnimation();
};
Ghost::Ghost(int x, int y){
    //std::cout << "ghost has been created" << std::endl;
    x_ = x;
    y_ = y;
    health_ = 5;
    velocity_ = 1;
    LoadAnimation();
};

Ghost::~Ghost(){
    //std::cout << "Ghost Deconstructor called" << std::endl;
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
    }
    //If moving right
    else if((cos(radians) * velocity_) > 0 && (xCollisionDirection_ == 0)){
        //Set xOffset
        x_ = x_ - xOffset_;
    }
    else {
        x_ += cos(radians) * velocity_;
        
    }
    //if moving down
    if((sin(radians) * velocity_) > 0 && (yCollisionDirection_ == -1)){
        //Set yOffset
        y_ = y_ - yOffset_;
    }
    //if moving up
    else if((sin(radians) * velocity_) < 0 && (yCollisionDirection_ == 0)){
        //Set yOffset
        y_ = y_ - yOffset_;
    }
    else {
    y_ += sin(radians) * velocity_;
    }
};

void Ghost::RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources){
    // Create the block that is the ghost
    //SDL_Rect sprite[3];
    SDL_Rect block;
    SDL_Rect block2;
    block.w = width_;
    block.h = height_;
    block.x = x_;
    block.y = y_;


    
    
    //SDL_SetTextureBlendMode(resources.getTexture("ghost sprite sheet"), SDL_BLENDMODE_NONE);
    if(SDL_RenderCopyEx(renderer, resources.getTexture("ghost sprite sheet"), &(animationSheet.at(Animation(anim_Sequence::walk))), &block, 0, NULL, SDL_FLIP_NONE) < 0){
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
    }

};

bool Ghost::Exists(){
    if(exists_ == true){
        return true;
    }
    else{
        return false;
    }
};

void Ghost::TakeDamage(int damage){
    health_ -= damage;
};

int32_t Ghost::GiveDamage(){
    uint32_t current_shoot_timer_ = SDL_GetTicks();
    if (current_shoot_timer_ > (shoot_timer_ + 1000)) {
        shoot_timer_ = SDL_GetTicks();
        return 1;
    }
    else{
        return 0;
    }
};

int Ghost::GivePoints(){
    return 1;
};



float Ghost::Animation(anim_Sequence animationSequence){
    switch(animationSequence){

        case anim_Sequence::walk:
        currentAnimTimer_ = SDL_GetTicks();
        if(currentAnimTimer_ > (animTimer_ + animSpeed_)) {
            animTimer_ = SDL_GetTicks();
                currentAnim++;
            for(currentAnim; currentAnim <= 3;){
                if(currentAnim == 3){
                    currentAnim = 0;
                }
                return currentAnim;
            }
        }
        return currentAnim;
    }
    return currentAnim;
};

void Ghost::LoadAnimation(){
    SDL_Rect sprite[3];
    sprite[0].w = 64;
    sprite[0].h = 64;
    sprite[0].x = 0;
    sprite[0].y = 0;

    sprite[1].x = 64;
    sprite[1].y = 0;
    sprite[1].w = 64;
    sprite[1].h = 64;

    sprite[2].w = 64;
    sprite[2].h = 64;
    sprite[2].x = 128;
    sprite[2].y = 0;

    animationSheet.push_back(sprite[0]);
    animationSheet.push_back(sprite[1]);
    animationSheet.push_back(sprite[2]);

}
