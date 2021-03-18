#include "character.h"
#include <iostream>

Character::Character(){
    std::cout << "The character has been created" << std::endl;
    //surface = IMG_Load("Resources/images/wizard_shooting.png");
}

void Character::SetTexture(SDL_Renderer* renderer){
   // texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void Character::Update(Direction direction){
    switch (direction){
        
        case Direction::kUp:
        pos_y = pos_y -speed;
        break;

        case Direction::kDown:
        pos_y = pos_y + speed;
        break;

        case Direction::kLeft:
        pos_x = pos_x - speed;
        break;

        case Direction::kRight:
        pos_x = pos_x + speed;
        break;

        case Direction::kRotateLeft:
        angle = angle + speed;
        break;

        case Direction::kRotateRight:
        angle = angle - speed;
        break;

    }
}