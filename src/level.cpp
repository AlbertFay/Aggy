#include "level.h"

Level::Level(){
    coordinates_.push_back(Coordinate(100, -100));
    coordinates_.push_back(Coordinate(500, -100));
    coordinates_.push_back(Coordinate(900, -100));
    coordinates_.push_back(Coordinate(-100, 100));
    coordinates_.push_back(Coordinate(-100, 500));
    coordinates_.push_back(Coordinate(-100, 900));
    coordinates_.push_back(Coordinate(1124, 100));
    coordinates_.push_back(Coordinate(1124, 500));
    coordinates_.push_back(Coordinate(1124, 900));
};

void Level::SpawnEnemies(std::vector<Enemy*> &enemies){
    int randomNumber;
    currentTimer_ = SDL_GetTicks();
    if(currentTimer_ > timer_ + randomTime_){
        timer_ = SDL_GetTicks();
        max_ = 8; //Max number of coordinates in vector
        randomNumber = std::round(min_ + (float)(rand()) / ((float)(RAND_MAX / (max_ - min_))));
        Ghost *ghost = new Ghost(700, 300);
        ghost->SetX(coordinates_.at(randomNumber).x_);
        ghost->SetY(coordinates_.at(randomNumber).y_);
        enemies.emplace_back(ghost);
        std::cout << "ghost has been created" << std::endl;
        max_ = 8000;
        randomTime_ = std::round(min_ + (float)(rand()) / ((float)(RAND_MAX / (max_ - min_))));
        std::cout << "randomTime = " << randomTime_ << std::endl;
        
    }
};