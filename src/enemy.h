#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include "renderable.h"

class Enemy: public Renderable{
    public:
    virtual void Update() = 0;
    virtual void Update(int x, int y) = 0;
    virtual ~Enemy() = default;
    virtual void SetXOffset(int offset) = 0;
    virtual void SetYOffset(int offset) = 0;
    virtual void SetXCollisionSpeed(int collisionDirection) = 0;
    virtual void SetYCollisionSpeed(int collisionDirection) = 0;
};

#endif