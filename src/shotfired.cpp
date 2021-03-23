#include "shotfired.h"

ShotFired::ShotFired(float start_x, float start_y, float angle, std::string filePath): x_pos_(start_x), y_pos_(start_y), angle_(angle), filepath_(filePath)  {
    float radians;
    radians = ( (angle_ - 90) * 3.1415926535) / 180.0;
    x_velocity_ = (velocity_)*(cos(radians) );
    y_velocity_ = (velocity_)* ( (-1)*sin(radians) );
}

ShotFired::~ShotFired() {
    std::cout << "ShotFired Deconstructor called" << std::endl;
}

bool ShotFired::Exists() {
    uint32_t currentTime = SDL_GetTicks();
    if(currentTime > lifetime_timer_ + 15000){
        exists_ = false;
    }
    return ShotFired::exists_;
}

void ShotFired::Update() {
    x_pos_ += x_velocity_;
    y_pos_ -= y_velocity_;
}

void ShotFired::RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources) {
    // Create the block that is the character
    SDL_Rect block;
    block.w = width;
    block.h = height;
    block.x = x_pos_;
    block.y = y_pos_;

    // Create Texture and Surfaces
   /* SDL_Texture* tex = NULL;
    SDL_Surface* surface = NULL;
    surface = IMG_Load(filepath_.c_str());
    if (surface == NULL){
        std::cerr << "surface did not get created" << std::endl;
    }
    tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (tex == NULL){
        std::cerr << "Texture did not get created" << std::endl;
    }
    // Free the surface
    SDL_FreeSurface(surface); */
    // Add character to the Render
    SDL_RenderCopyEx(renderer, resources.getTexture("fireball"), NULL, &block, (angle_ + 90), NULL, SDL_FLIP_NONE);
}
