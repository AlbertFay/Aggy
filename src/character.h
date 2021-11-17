#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "shotfired.h"
#include "resource-manager.h"
#include <vector>
#include "SDL2/SDL_ttf.h"

class Character {
  public:
    enum class Direction {kUp, kDown, kLeft, kRight, kRotateRight, kRotateLeft};
    std::vector<ShotFired> vecShotFired;
    int score = 0;
  
    Character(std::vector<Renderable*> &renderables);
    void Shoot();
    void Update(Direction direction);
    void Update();
    void SetTexture(SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer, ResourceManager &resources);
    void Died();
    void TakeDamage(int damage) {health_ -= damage;};
    void LoadResources(SDL_Renderer *renderer, ResourceManager &resources);

    // Getters/Setters
    float GetAngle() {
      return angle;
    };

    float GetX() {
      return pos_x;
    };
    float GetY() {
      return pos_y;
    };
    float GetWidth() {
      return width;
    };
    float GetHeight() {
      return height;
    };
    bool IsAlive(){
      return isAlive_;
    }
    /*
    0 means collision on right
    -1 means collision on left
    1 means no collision
    */
    void SetXCollisionSpeed(float speed) {
      if(speed == 0){
        x_right_collision_speed = 0;
      }
      if(speed == -1){
        x_left_collision_speed = 0;
      }
      if (speed == 1){
        x_right_collision_speed = 1;
        x_left_collision_speed = 1;
      }
    };
    /*
    0 means collision on top
    -1 means collision on bottom
    1 means no collision
    */
    void SetYCollisionSpeed(float speed) {
      if(speed == 0){
        y_up_collision_speed = 0;
      } 
      if(speed == -1){
        y_down_collision_speed = 0;
      }
      if (speed == 1){
        y_up_collision_speed = 1;
        y_down_collision_speed = 1;
      }
    };
    void SetXOffset(int offset){
      pos_x = pos_x - offset;
    };
    void SetYOffset(int offset){
      pos_y = pos_y - offset;
    };
  private:
    bool isAlive_ = true;
    Direction direction = Direction::kUp;
    float speed = 3;
    float angle = 0, rotationSpeed = 3.5;
    float width = 100, height = 100;
    float pos_x = 0, pos_y = 0;
    float hand_angle_ = (((angle - 2.8)* 3.1415926535) / 180.0);
    float hand_distance_ = (width * .33);
    float x_left_collision_speed = 1;
    float x_right_collision_speed = 1;
    float y_up_collision_speed = 1;
    float y_down_collision_speed = 1;
    std::vector<Renderable*> &renderables_;
    int health_ = 5;
    int max_health = 5;

    uint32_t shoot_timer_ = SDL_GetTicks();



};

#endif