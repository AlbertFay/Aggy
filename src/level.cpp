#include "level.h"

Level::Level(){
    coordinates_.push_back(Coordinate(700, 700));
    coordinates_.push_back(Coordinate(700, 900));
};

void Level::SpawnEnemies(std::vector<Enemy*> &enemies){
    int randomNumber;
    currentTimer_ = SDL_GetTicks();
    if(currentTimer_ > timer_ + randomTime_){
        timer_ = SDL_GetTicks();
        max_ = 1;
        randomNumber = std::round(min_ + (float)(rand()) / ((float)(RAND_MAX / (max_ - min_))));
        Ghost *ghost = new Ghost(700, 300);
        ghost->SetX(coordinates_.at(randomNumber).x_);
        ghost->SetY(coordinates_.at(randomNumber).y_);
        enemies.emplace_back(ghost);
        max_ = 2000;
        randomTime_ = std::round(min_ + (float)(rand()) / ((float)(RAND_MAX / (max_ - min_))));
        std::cout << "randomTime = " << randomTime_ << std::endl;
        
    }
};