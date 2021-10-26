#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include "renderable.h"

class Enemy: public Renderable{
    public:
    virtual void Update() = 0;
    virtual ~Enemy() = default;
};

#endif