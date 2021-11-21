#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "enemy.h"

class Level {
    public:
    struct Coordinate{
       int x_, y_;
       Coordinate(int x, int y): x_(x), y_(y) {}
    };
    
    Level(std::vector<Enemy*> enemies);
    void SpawnEnemies();
    private:
    std::vector<Coordinate> coordinates_;
    uint32_t timer_ = SDL_GetTicks();
    uint32_t currentTimer_= SDL_GetTicks();
    int randTime_ = std::rand() % 2000;
};

#endif