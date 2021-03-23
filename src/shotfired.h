#ifndef SHOTFIRED_H
#define SHOTFIRED_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <cmath>
#include <iostream>
#include "renderable.h"
#include "math.h"
#include "resource-manager.h"

class ShotFired : public Renderable{
  public:
    ShotFired(float start_x, float start_y, float angle, std::string filePath);
    ~ShotFired();
    void RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources) ;
    void Update() ;
    bool Exists() ;

  private:
    SDL_Surface *surface_;

    float exists_ = true;
    float velocity_ = 1;
    float angle_;
    float x_velocity_ = 0;
    float y_velocity_ = 0;
    float x_pos_;
    float y_pos_;
    float width = 50, height = 50;
    std::string filepath_;
};

#endif