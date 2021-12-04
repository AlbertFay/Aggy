#include <iostream>
#include "character.h"

Character::Character(std::vector<Renderable*> &renderables){
    std::cout << "The character has been created" << std::endl;
    //surface = IMG_Load("C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
    hitBox_.w = width -20;
    hitBox_.h = height -4;
    hitBox_.x = pos_x +2;
    hitBox_.y = pos_y +2;
};

Character::Character(){
    //testenemies_ = testenemies;
    std::cout << "The character has been created" << std::endl;
    //surface = IMG_Load("C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
    hitBox_.w = width -20;
    hitBox_.h = height -4;
    hitBox_.x = pos_x +2;
    hitBox_.y = pos_y +2;
};

std::vector<std::unique_ptr<Renderable>>&& Character::Shoot(std::vector<std::unique_ptr<Renderable>> &&testenemies){
    if(energy >= 5){
        uint32_t current_shoot_timer_ = SDL_GetTicks();
        if (current_shoot_timer_ > (shoot_timer_ + 150)) {
            
            //ShotFired *firedShot = new ShotFired((hand_distance_ * cos(hand_angle_) + pos_x), (-hand_distance_ * sin(hand_angle_) + pos_y), angle, energy);
            //renderables_.emplace_back(firedShot);

            std::unique_ptr<ShotFired> pointer(new ShotFired((hand_distance_ * cos(hand_angle_) + pos_x), (-hand_distance_ * sin(hand_angle_) + pos_y), angle, energy));
            testenemies.push_back(std::move(pointer));

            shoot_timer_ = SDL_GetTicks();
            energy_timer_ = SDL_GetTicks();
        }
    }
    return std::move(testenemies);
};

void Character::Render(SDL_Renderer* renderer, ResourceManager &resources) {

    // Create the block that is the character
    SDL_Rect block;
    block.w = width;
    block.h = height;
    block.x = pos_x;
    block.y = pos_y;

    //Temp code to draw rectangle around character
    hitBox_.w = width ;
    hitBox_.h = height;
    hitBox_.x = pos_x ;
    hitBox_.y = pos_y ;

    // Add character to the Render
    SDL_RenderCopyEx(renderer, (resources.getTexture("character")), NULL, &block, angle, NULL, SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    //Temp code to draw rectangle around character
    SDL_RenderDrawRect(renderer, &hitBox_);

    //Automatically regain health after certain time
    uint32_t current_energy_timer = SDL_GetTicks();
    if(current_energy_timer > (energy_timer_ + 2500) && energy < max_energy){
        energy_timer_ = SDL_GetTicks();
        if(energy <= 80){
            energy += 20;
        }
        else{
            energy += (max_energy - energy);
        }

    }

};

void Character::Update(Direction direction){
    double rads = atan2((mousey - (pos_y + (height / 2))), (mousex - (pos_x + (width / 2))));
    angle = ((rads * 180) / 3.14159265) + 90;
    switch (direction){
        
        case Direction::kUp:
        pos_y -= speed_ * y_up_collision_speed;
        hitBox_.y = pos_y;
        break;

        case Direction::kDown:
        pos_y += speed_ * y_down_collision_speed;
        hitBox_.y = pos_y;
        break;

        case Direction::kLeft:
        pos_x -= speed_ * x_left_collision_speed;
        hitBox_.x = pos_x;
        break;

        case Direction::kRight:
        pos_x += speed_ * x_right_collision_speed;
        hitBox_.x = pos_x;
        break;

        case Direction::kRotateLeft:
        //angle -= rotationSpeed;
        break;

        case Direction::kRotateRight:
        //angle += rotationSpeed;
        break;

    }
    if(health_ <= 0){
        isAlive_ = false;
    }
};

void Character::Update(){
    double rads = atan2((mousey - (pos_y + (height / 2))), (mousex - (pos_x + (width / 2))));
    angle = ((rads * 180) / 3.14159265) + 90;

    if(health_ <= 0){
        isAlive_ = false;
    }
};

void Character::Sprint(int speed){
    if(energy >=1){
        uint32_t current_sprint_timer_ = SDL_GetTicks();
        if (current_sprint_timer_ > (sprint_timer_ + 100)) {
            speed_ = speed;
            energy -= 1;
            energy_timer_ = SDL_GetTicks();
            sprint_timer_ = SDL_GetTicks();
        }
    }
    double rads = atan2((mousey - (pos_y + (height / 2))), (mousex - (pos_x + (width / 2))));
    angle = ((rads * 180) / 3.14159265) + 90;

    if(health_ <= 0){
        isAlive_ = false;
    }
};

void Character::Died(){
    isAlive_ = false; 
};

void Character::LoadResources(SDL_Renderer *renderer, ResourceManager &resources){
    resources.LoadTexture(renderer, "character", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
    resources.LoadTexture(renderer, "fireball", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/red_fireball.png");
};