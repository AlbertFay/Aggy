#include <iostream>
#include "character.h"

Character::Character(std::vector<Renderable*> &renderables):renderables_(renderables){
    std::cout << "The character has been created" << std::endl;
    //surface = IMG_Load("C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
}

void Character::Shoot(){
    uint32_t current_shoot_timer_ = SDL_GetTicks();
    if (current_shoot_timer_ > (shoot_timer_ + 50)) {
        std::cout << "ShotFired object being created" << std::endl;
        
        ShotFired *firedShot = new ShotFired((hand_distance_ * cos(hand_angle_) + pos_x), (-hand_distance_ * sin(hand_angle_) + pos_y), angle);
        renderables_.emplace_back(firedShot);

        shoot_timer_ = SDL_GetTicks();
        std::cout << "ShotFired object created" << std::endl;
    }
}

void Character::Render(SDL_Renderer* renderer, ResourceManager &resources) {

    // Create the block that is the character
    SDL_Rect block;
    block.w = width;
    block.h = height;
    block.x = pos_x;
    block.y = pos_y;

    SDL_Rect rectangle;
    rectangle.w = width;
    rectangle.h = height;
    rectangle.x = pos_x;
    rectangle.y = pos_y;


    // Add character to the Render
    if(resources.getTexture("character") == NULL){
        std::cerr << "Character.cpp GetTexture = NuLL" << std::endl;
    }
    SDL_RenderCopyEx(renderer, (resources.getTexture("character")), NULL, &block, angle, NULL, SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderDrawRect(renderer, &rectangle);
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

void Character::Move(){
    
}