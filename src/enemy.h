#ifndef ENEMY_H
#define ENEMY_H
#include <string>

class Enemy{
    public:
    Enemy();
    virtual void Update() = 0;
    virtual ~Enemy() = default;
};

#endif