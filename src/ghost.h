#ifndef GHOST_H
#define GHOST_H
#include "enemy.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "renderable.h"
#include "resource-manager.h"

class Ghost: public Enemy{
    public:
        Ghost();
        ~Ghost();
        void Update();
        void RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources);
        float GetX(){return x_;};
        float GetY(){return y_;};
        float GetHeight(){return width_;};
        float GetWidth(){return height_;};
        bool Exists(); //This function checks to see if the object is still alive or not
        void Died(){exists_ = false;};
    private:
    int x_, y_, angle_;
    int width_ = 64;
    int height_ = 64;
    bool exists_;
    int velocity_, x_velocity_, y_velocity_;
    int health_ = 5;
};

#endif