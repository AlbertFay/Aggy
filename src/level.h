#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "enemy.h"
#include <cmath>
#include "ghost.h"

class Level {
    public:
    struct Coordinate{
       int x_, y_;
       Coordinate(int x, int y): x_(x), y_(y) {}
    };
    
    Level();
    void SpawnEnemies(std::vector<Enemy*> &enemies);
    private:
    std::vector<Coordinate> coordinates_;
    uint32_t timer_ = SDL_GetTicks();
    uint32_t currentTimer_= SDL_GetTicks();
    int min_ = 0;
    int max_ = 2000;
    int randomTime_ = std::round(min_ + (float)(rand()) / ((float)(RAND_MAX / (max_ - min_))));

};

#endif