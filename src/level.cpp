#include "level.h"

/**
 * Default constructor for Level. It also creates
 * the starting coordinates for enemies to spawn
 */
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

/**
 * Uses Timer to randomly create enemies objects at random 
 * spawn points at random times.
 */
void Level::SpawnEnemies(std::vector<std::shared_ptr<Enemy>> &enemies){
    int randomNumber;
    currentTimer_ = SDL_GetTicks();
    if(currentTimer_ > timer_ + randomTime_){
        timer_ = SDL_GetTicks();
        max_ = 8; //Max number of coordinates in vector
        randomNumber = std::round(min_ + (float)(rand()) / ((float)(RAND_MAX / (max_ - min_))));
        std::shared_ptr<Ghost> ghost = std::make_shared<Ghost>();
        ghost->SetX(coordinates_.at(randomNumber).x_);
        ghost->SetY(coordinates_.at(randomNumber).y_);
        enemies.push_back(ghost);
        max_ = 8000;
        randomTime_ = std::round(min_ + (float)(rand()) / ((float)(RAND_MAX / (max_ - min_))));
        
    }
};