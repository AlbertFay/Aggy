#include "level.h"

Level::Level(std::vector<Enemy*> enemies){
    coordinates_.emplace_back(Coordinate(700, 700));
};

void Level::SpawnEnemies(){
    currentTimer_ = SDL_GetTicks();
    if(currentTimer_ < timer_ + randTime_){
        timer_ = SDL_GetTicks();
        randTime_ = std::rand() % 2000;
        
    }
};