#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Character {
  public:
    enum class Direction {kUp, kDown, kLeft, kRight, kRotateRight, kRotateLeft};
  
    Character();
    void Update(Direction direction);
    void SetTexture(SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);

    // Getters/Setters
    float GetAngle() {
      return angle;
    }

  private:
    bool isAlive_;
    Direction direction = Direction::kUp;
    float speed = 2;
    float angle = 0, rotationSpeed = 3;
    float width = 200, height = 200;
    float pos_x = 0, pos_y = 0;

};

#endif