#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Character {
  public:
    enum class Direction {kUp, kDown, kLeft, kRight, kRotateRight, kRotateLeft};
    float pos_x = 0, pos_y = 0;
    float width = 200, height = 200;
    float angle = 0, rotationSpeed = 10;
    //SDL_Texture *texture;
   // SDL_Surface *surface;

  
    Character();
    void Update(Direction direction);
    void SetTexture(SDL_Renderer* renderer);

  private:
    bool isAlive_;
    Direction direction = Direction::kUp;
    float speed = 2;

};

#endif