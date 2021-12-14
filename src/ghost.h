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
        ~Ghost() override;
        void Update(int x, int y) override;
        void Update() override;
        void RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources) override;
        float GetX() override {return x_;};
        float GetY() override {return y_;};
        float GetHeight() override {return width_;};
        float GetWidth() override {return height_;};
        void SetX(int x) {x_ = x;};
        void SetY(int y) {y_ = y;};
        void SetXOffset(int offset) override {xOffset_ = offset;};
        void SetYOffset(int offset) override {xOffset_ = offset;};
        void SetYCollisionSpeed(int collisionDirection) override {
            if (collisionDirection != 1){
                yCollisionDirection_ = collisionDirection;
                // std::cout << "collision direction in h file" << yCollisionDirection_ << std::endl;
            }
            else{
                //std::cout << "THis shouldnt be running" << std::endl;
                yCollisionDirection_ = 1;
            }
        };
        void SetXCollisionSpeed(int collisionDirection) override {
            if (collisionDirection != 1){
                xCollisionDirection_ = collisionDirection;
                // std::cout << "collision direction in h file" << xCollisionDirection_ << std::endl;
            }
            else{
                // std::cout << "THis shouldnt be running" << std::endl;
                xCollisionDirection_ = 1;
            }
        };
        bool Exists() override; //This function checks to see if the object is still alive or not
        void Died() override {exists_ = false;};
        void TakeDamage(int damage) override;
        int GetHealth() override {return health_;};
        int GiveDamage() override;
        int GivePoints() override;
        float Animation(anim_Sequence animationSequence);
        void LoadAnimation();

    private:
    float x_, y_, angle_;
    float width_ = 64;
    float height_ = 64;
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