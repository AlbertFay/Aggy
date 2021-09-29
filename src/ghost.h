#ifndef GHOST_H
#define GHOST_H
#include "enemy.h"
#include "SDL2/SDL.h"
#include "renderable.h"

class Ghost: public Enemy{
    public:
        Ghost();
        void Update();
        void RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources);
        float GetX(){return x_;};
        float GetY(){return y_;};
        float GetHeight(){return width_;};
        float GetWidth(){return height_;};
        bool Exists(); //This function checks to see if the object is still alive or not
        void Died(){exists_ = false;};
        ~Ghost();
    private:
    int x_, y_, width_, height_;
    bool exists_;
    int velocity_, x_velocity_, y_velocity_;
};

#endif