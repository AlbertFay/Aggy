#include "character.h"
#include <iostream>

Character::Character(){
    //std::cout << "The character has been created" << std::endl;
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

    }
}