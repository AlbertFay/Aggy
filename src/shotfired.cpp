#include "shotfired.h"

/**
 * Constructor for ShotFired, sets the angle, the x and y
 * velocity, and reduces character energy.
 */
ShotFired::ShotFired(float start_x, float start_y, float angle, double &energy): x_pos_(start_x), y_pos_(start_y), angle_(angle) {
    std::cout << "Fireball has been created" << std::endl;
    float radians;
    radians = ( (angle_ - 90) * 3.1415926535) / 180.0;
    x_velocity_ = (velocity_)*(cos(radians) );
    y_velocity_ = (velocity_)* ( (-1)*sin(radians) );
    energy -= 5;
}

/**
 * Deconstructor for ShotFired
 */
ShotFired::~ShotFired() {
    std::cout << "Fireball has been destroyed" << std::endl;
   // std::cout << "ShotFired Deconstructor called" << std::endl;
}

/**
 * Checks to see if ShotFired still exists. Also uses
 * a timer to make ShotFired not exist after x seconds.
 */
bool ShotFired::Exists() {
    uint32_t currentTime = SDL_GetTicks();
    if(currentTime > lifetime_timer_ + 8000){
        exists_ = false;
    }
    return ShotFired::exists_;
}

/**
 * Updates the position on the map.
 */
void ShotFired::Update() {
    x_pos_ += x_velocity_;
    y_pos_ -= y_velocity_;
}

/**
 * Sets ShotFired::exists_ to false;
 */
void ShotFired::Died(){
    exists_ = false;
}

/**
 * Uses SDL_Renderer to render ShotFired object to the screen.
 */
void ShotFired::RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources) {

    // Create the block that is the fireball
    SDL_Rect block;
    block.w = width;
    block.h = height;
    block.x = x_pos_;
    block.y = y_pos_;

    SDL_RenderCopyEx(renderer, resources.getTexture("fireball"), NULL, &block, (angle_ + 90), NULL, SDL_FLIP_NONE);
}
