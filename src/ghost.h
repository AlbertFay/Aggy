#ifndef GHOST_H
#define GHOST_H
#include "enemy.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "renderable.h"
#include "resource-manager.h"
#include <cmath>
#include <vector>

class Ghost: public Enemy{
    public:
        enum class anim_Sequence{walk};
        Ghost();
        Ghost(int x, int y);
        ~Ghost();
        void Update(int x, int y);
        void Update();
        void RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources);
        float GetX(){return x_;};
        float GetY(){return y_;};
        float GetHeight(){return width_;};
        float GetWidth(){return height_;};
        void SetX(int x){x_ = x;};
        void SetY(int y){y_ = y;};
        void SetXOffset(int offset) {xOffset_ = offset;};
        void SetYOffset(int offset) {xOffset_ = offset;};
        void SetYCollisionSpeed(int collisionDirection) {
            if (collisionDirection != 1){
                yCollisionDirection_ = collisionDirection;
                // std::cout << "collision direction in h file" << yCollisionDirection_ << std::endl;
            }
            else{
                //std::cout << "THis shouldnt be running" << std::endl;
                yCollisionDirection_ = 1;
            }
        };
        void SetXCollisionSpeed(int collisionDirection) {
            if (collisionDirection != 1){
                xCollisionDirection_ = collisionDirection;
                // std::cout << "collision direction in h file" << xCollisionDirection_ << std::endl;
            }
            else{
                // std::cout << "THis shouldnt be running" << std::endl;
                xCollisionDirection_ = 1;
            }
        };
        bool Exists(); //This function checks to see if the object is still alive or not
        void Died(){exists_ = false;};
        void TakeDamage(int damage);
        int GetHealth(){return health_;};
        int GiveDamage();
        int GivePoints();
        float Animation(anim_Sequence animationSequence);
        void LoadAnimation();

    private:
    double x_, y_, angle_;
    int width_ = 64;
    int height_ = 64;
    bool exists_ = true;
    int velocity_, x_velocity_, y_velocity_;
    int xOffset_ = 0, yOffset_ = 0, xCollisionDirection_ = 1, yCollisionDirection_ = 1;
    int health_ = 5;
    int animSpeed_ = 250;
    std::vector<SDL_Rect> animationSheet;

    uint32_t shoot_timer_ = SDL_GetTicks();
    uint32_t animTimer_= SDL_GetTicks();
    uint32_t currentAnimTimer_ = 0;
    float currentAnim = 0;
};

#endif