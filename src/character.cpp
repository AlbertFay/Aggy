#include "character.h"
#include <iostream>

Character::Character(){
    //std::cout << "The character has been created" << std::endl;
}

void Character::Update(Direction direction){
    switch (direction){
        case Direction::kUp:
        std::cout << "This is kUp" << "\n";
        pos_y = pos_y -speed;
        break;
        case Direction::kDown:
        std::cout << "This is kDown" << "\n";
        pos_y = pos_y + speed;
        break;
        case Direction::kLeft:
        std::cout << "This is kLeft" << "\n";
        pos_x = pos_x - speed;
        break;
        case Direction::kRight:
        std::cout << "This is kRight" << "\n";
        pos_x = pos_x + speed;
        break;

    }
}