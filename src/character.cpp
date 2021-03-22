#include <iostream>
#include "character.h"

Character::Character(){
    std::cout << "The character has been created" << std::endl;
    //surface = IMG_Load("C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
}

void Character::Shoot(std::vector<Renderable*> &renderables){
    uint32_t current_shoot_timer_ = SDL_GetTicks();
    if (current_shoot_timer_ > (shoot_timer_ + 1000)) {
        std::cout << "ShotFired object being created" << std::endl;
        ShotFired *firedShot = new ShotFired((height * .2), (width * .4), angle, "C:/C++ Development/C++ Projects/Aggy/Resources/Images/red_fireball.png");
        //ShotFired *ptr = &firedShot;
        renderables.emplace_back(firedShot);
        shoot_timer_ = SDL_GetTicks();
        std::cout << "ShotFired object created" << std::endl;
    }
}

void Character::Render(SDL_Renderer* renderer) {

    // Create the block that is the character
    SDL_Rect block;
    block.w = width;
    block.h = height;
    block.x = pos_x;
    block.y = pos_y;

    // Create Texture and Surfaces
    SDL_Texture* tex;
    SDL_Surface* surface;
    surface = IMG_Load("C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
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
    SDL_RenderCopyEx(renderer, tex, NULL, &block, angle, NULL, SDL_FLIP_NONE);
}

void Character::Update(Direction direction){
    switch (direction){
        
        case Direction::kUp:
        pos_y -= speed;
        break;

        case Direction::kDown:
        pos_y += speed;
        break;

        case Direction::kLeft:
        pos_x -= speed;
        break;

        case Direction::kRight:
        pos_x += speed;
        break;

        case Direction::kRotateLeft:
        angle -= rotationSpeed;
        break;

        case Direction::kRotateRight:
        angle += rotationSpeed;
        break;

    }
}