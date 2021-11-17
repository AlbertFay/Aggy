#include <iostream>
#include "character.h"

Character::Character(std::vector<Renderable*> &renderables):renderables_(renderables){
    std::cout << "The character has been created" << std::endl;
    //surface = IMG_Load("C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
}

void Character::Shoot(){
    uint32_t current_shoot_timer_ = SDL_GetTicks();
    if (current_shoot_timer_ > (shoot_timer_ + 150)) {
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

    //Temp code to draw rectangle around character
    SDL_Rect rectangle;
    rectangle.w = width;
    rectangle.h = height;
    rectangle.x = pos_x;
    rectangle.y = pos_y;

    // Add character to the Render
    SDL_RenderCopyEx(renderer, (resources.getTexture("character")), NULL, &block, angle, NULL, SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    //Temp code to draw rectangle around character
    //SDL_RenderDrawRect(renderer, &rectangle);

}

void Character::Update(Direction direction){
    switch (direction){
        
        case Direction::kUp:
        pos_y -= speed * y_up_collision_speed;
        break;

        case Direction::kDown:
        pos_y += speed * y_down_collision_speed;
        break;

        case Direction::kLeft:
        pos_x -= speed * x_left_collision_speed;
        break;

        case Direction::kRight:
        pos_x += speed * x_right_collision_speed;
        break;

        case Direction::kRotateLeft:
        angle -= rotationSpeed;
        break;

        case Direction::kRotateRight:
        angle += rotationSpeed;
        break;

    }
    if(health_ <= 0){
        isAlive_ = false;
    }
}
void Character::Update(){
    if(health_ <= 0){
        isAlive_ = false;
    }
}

void Character::Died(){
    isAlive_ = false; 
};

void Character::LoadResources(SDL_Renderer *renderer, ResourceManager &resources){
  resources.LoadTexture(renderer, "character", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
};