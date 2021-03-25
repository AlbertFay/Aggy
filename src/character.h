#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "shotfired.h"
#include "resource-manager.h"
#include <vector>

class Character {
  public:
    enum class Direction {kUp, kDown, kLeft, kRight, kRotateRight, kRotateLeft};
    std::vector<ShotFired> vecShotFired;
  
    Character(std::vector<Renderable*> &renderables);
    void Shoot();
    void Update(Direction direction);
    void SetTexture(SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer, ResourceManager &resources);

    // Getters/Setters
    float GetAngle() {
      return angle;
    }

  private:
    bool isAlive_;
    Direction direction = Direction::kUp;
    float speed = 3;
    float angle = 0, rotationSpeed = 3.5;
    float width = 100, height = 100;
    float pos_x = 0, pos_y = 0;
    float hand_angle_ = (((angle - 2.8)* 3.1415926535) / 180.0);
    float hand_distance_ = (width * .33);
    std::vector<Renderable*> &renderables_;

    uint32_t shoot_timer_ = SDL_GetTicks();

};

#endif