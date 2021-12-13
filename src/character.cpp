#include <iostream>
#include "character.h"

// Character default constructor
Character::Character(){
    hitBox_.w = width -20;
    hitBox_.h = height -4;
    hitBox_.x = pos_x +2;
    hitBox_.y = pos_y +2;
};

/**
 * Checks to see if character has enough energy to shoot
 * and uses timer to only allow shots every x milliseconds.
 * Creates ShotFired object and moves it into vector
*/
std::vector<std::unique_ptr<Renderable>>&& Character::Shoot(std::vector<std::unique_ptr<Renderable>> &&FiredShots){
    //Cant shoot if there isn't enough energy
    if(energy >= 5){
        //Only allows 1 shot every x milliseconds
        uint32_t current_shoot_timer_ = SDL_GetTicks();
        if (current_shoot_timer_ > (shoot_timer_ + 150)) {
            //Create ShotFired Object on heap and move into FiredShots vector            
            std::unique_ptr<ShotFired> pointer(new ShotFired((hand_distance_ * cos(hand_angle_) + pos_x), (-hand_distance_ * sin(hand_angle_) + pos_y), angle, energy));
            FiredShots.push_back(std::move(pointer));

            shoot_timer_ = SDL_GetTicks();
            energy_timer_ = SDL_GetTicks();
        }
    }
    return std::move(FiredShots);
};

/**
 * Uses SDL_renderer to render character to screen
 * and also adds health to character automatically
 * after x milliseconds
*/
void Character::Render(SDL_Renderer* renderer, ResourceManager &resources) {

    // Create the block that is the character
    SDL_Rect block;
    block.w = width;
    block.h = height;
    block.x = pos_x;
    block.y = pos_y;

    //Create HitBox dimensions for character
    hitBox_.w = width ;
    hitBox_.h = height;
    hitBox_.x = pos_x ;
    hitBox_.y = pos_y ;

    // Add character to the Render
    SDL_RenderCopyEx(renderer, (resources.getTexture("character")), NULL, &block, angle, NULL, SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    //Temp code to draw rectangle around character
    SDL_RenderDrawRect(renderer, &hitBox_);

    //Automatically regain health after x time has passed
    uint32_t current_energy_timer = SDL_GetTicks();
    if(current_energy_timer > (energy_timer_ + 2500) && energy < max_energy){
        energy_timer_ = SDL_GetTicks();
        //If/else to insure energy doesn't exceed max energy
        if(energy <= 80){
            energy += 20;
        }
        else{
            energy += (max_energy - energy);
        }

    }

};

//Character Update function for when character is moving
void Character::Update(Direction direction){
    //Calculate angle in radians from character center to mouse
    double rads = atan2((mousey - (pos_y + (height / 2))), (mousex - (pos_x + (width / 2))));
    //Convert radians to degrees
    angle = ((rads * 180) / 3.14159265) + 90;
    // 
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
    }
    if(health_ <= 0){
        isAlive_ = false;
    }
};

//Character Update function for when character isn't moving
void Character::Update(){
    double rads = atan2((mousey - (pos_y + (height / 2))), (mousex - (pos_x + (width / 2))));
    angle = ((rads * 180) / 3.14159265) + 90;

    if(health_ <= 0){
        isAlive_ = false;
    }
};

//Character Update Function to sprint 
void Character::Sprint(int speed){
    //Character cant sprint if there is not enough energy
    if(energy >=1){
        //Reduces energy level every x milliseconds
        uint32_t current_sprint_timer_ = SDL_GetTicks();
        if (current_sprint_timer_ > (sprint_timer_ + 100)) {
            speed_ = speed;
            energy -= 1;
            energy_timer_ = SDL_GetTicks();
            sprint_timer_ = SDL_GetTicks();
        }
    }
    //Sets character angle based on where mouse is
    double rads = atan2((mousey - (pos_y + (height / 2))), (mousex - (pos_x + (width / 2))));
    angle = ((rads * 180) / 3.14159265) + 90;

    if(health_ <= 0){
        isAlive_ = false;
    }
};

//Loads texture into resources vector for use
void Character::LoadResources(SDL_Renderer *renderer, ResourceManager &resources){
    resources.LoadTexture(renderer, "character", "../Resources/Images/wizard_shooting.png");
    resources.LoadTexture(renderer, "fireball", "../Resources/Images/red_fireball.png");
};

//Resets character to original state 
void Character::Reset(){
    pos_x = 512;
    pos_y = 512;
    health_ = 5;
    energy = 100;
    score = 0;
    isAlive_ = true;
};