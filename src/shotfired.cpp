#include "shotfired.h"

ShotFired::ShotFired(float start_x, float start_y, float angle, std::string filePath): x_pos_(start_x), y_pos_(start_y), angle_(angle), filepath_(filePath)  {
    x_velocity_ = (velocity_)*(cos(angle_));
    y_velocity_ = (velocity_)*(sin(angle_));
}

ShotFired::~ShotFired() {
    std::cout << "ShotFired Deconstructor called" << std::endl;
}

bool ShotFired::Exists() {
    std::cout << "ShotFired::Exists() was called" << std::endl;
    return ShotFired::exists_;
}

void ShotFired::Update() {
    std::cout << "ShotFired::Update() was called" << std::endl;
    x_pos_ += x_velocity_;
    y_pos_ += y_velocity_;
}

void ShotFired::RenderRenderable(SDL_Renderer* renderer) {
    std::cout << "ShotFired is being rendered" << std::endl;
    std::cout << "Filepath: " <<filepath_ << std::endl;
    // Create the block that is the character
    SDL_Rect block;
    block.w = width;
    block.h = height;
    block.x = x_pos_;
    block.y = y_pos_;

    // Create Texture and Surfaces
    SDL_Texture* tex;
    SDL_Surface* surface;
    surface = IMG_Load(filepath_.c_str());
    if (surface == NULL){
        std::cerr << "surface did not get created" << std::endl;
    }
    tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (tex == NULL){
        std::cerr << "Texture did not get created" << std::endl;
    }
    // Free the surface
    SDL_FreeSurface(surface); 
    // Add character to the Render
    SDL_RenderCopyEx(renderer, tex, NULL, &block, angle_, NULL, SDL_FLIP_NONE);
    std::cout << "End of ShotFire Rendering" << std::endl;
}
