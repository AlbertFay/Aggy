#include "ghost.h"

/**
 * Default Constructor for Ghost. Sets health_, starting
 * position, speed, and loads animation sequence
 */
Ghost::Ghost(){
    //Setup starting position
    x_ = 300;
    y_ = 300;
    health_ = 5;
    //Set speed
    velocity_ = 1;
    LoadAnimation();
};

/**
 * Ghost constructor, specifies starting location
 */
Ghost::Ghost(int x, int y): x_(x), y_(y){
    // Set starting position
    health_ = 5;
    velocity_ = 1;
    LoadAnimation();
};

/**
 * Ghost deconstructer
 */
Ghost::~Ghost() {};

void Ghost::Update(){
    //I dont think I need this function but Update() is a renderable virtual function 
};

/**
 * Updates Ghost position and angle, moving towards character
 */
void Ghost::Update(int x, int y){
    //Updates, moving towards character
    int x_difference = (x - x_);
    int y_difference = (y - y_);
    double radians = atan2(y_difference, x_difference);
    angle_ = ((radians * 180)/ 3.14159) + 90; //Converted to degrees from radians
    //Update x and y with new position moving towards character
    //if moving left
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

/**
 * Uses SDL_Renderer to render ghost object
 */
void Ghost::RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources){
    // Create the block where ghost will be rendered
    SDL_Rect block;
    block.w = width_;
    block.h = height_;
    block.x = x_;
    block.y = y_;
    
    //Render Ghost, src rectangle is determined by Animation()
    if(SDL_RenderCopyEx(renderer, resources.getTexture("ghost sprite sheet"), &(animationSheet.at(Animation(anim_Sequence::walk))), &block, 0, NULL, SDL_FLIP_NONE) < 0){
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
    }

};

/**
 * Returns whether the Ghost object still
 * exists or not.
 */
bool Ghost::Exists(){
    return exists_;
};

/**
 * Subtracts damage from ghost health;
 */
void Ghost::TakeDamage(int damage){
    health_ -= damage;
};

/**
 * Determines how much damage to give the player
 * and uses Timer to time how often ghost can
 * damage player.
 */
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

/**
 * Determines how many points to give
 * the player upon killing a ghost
 */
int Ghost::GivePoints(){
    return 1;
};

/**
 * Uses a timer to cycle through the animation sprites at
 * a certain rate, then returns what sprite is suppose to
 * be animated. Can add different animation patterns
 */
float Ghost::Animation(anim_Sequence animationSequence){
    switch(animationSequence){

        case anim_Sequence::walk:
        currentAnimTimer_ = SDL_GetTicks();
        if(currentAnimTimer_ > (animTimer_ + animSpeed_)) {
            animTimer_ = SDL_GetTicks();
                currentAnim++;
            for(currentAnim; currentAnim <= 4;){
                if(currentAnim == 4){
                    currentAnim = 0;
                }
                return currentAnim;
            }
        }
        return currentAnim;
    }
    return currentAnim;
};

/**
 * For Ghost object, create a vector of SDL_Rects
 * and assign rects to spritesheet for animation.
 */
void Ghost::LoadAnimation(){
    SDL_Rect sprite[4];
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

    sprite[3].x = 64;
    sprite[3].y = 0;
    sprite[3].w = 64;
    sprite[3].h = 64;

    animationSheet.push_back(sprite[0]);
    animationSheet.push_back(sprite[1]);
    animationSheet.push_back(sprite[2]);
    animationSheet.push_back(sprite[3]);

}
