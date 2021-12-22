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
    ShotFired(float start_x, float start_y, float angle, double &energy);
    ~ShotFired() override;
    void RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources) override;
    void Update() override;
    bool Exists() override;
    void Died() override;
    float GetX() override {
      return x_pos_;
    };
    float GetY() override {
      return y_pos_;
    };
    float GetWidth() override {
      return width;
    };
    float GetHeight() override {
      return height;
    }

  private:
    SDL_Surface *surface_;
    
    float exists_ = true;
    int velocity_ = 4;
    float angle_ = 0;
    float x_velocity_ = 0;
    float y_velocity_ = 0;
    float x_pos_ = 0;
    float y_pos_ = 0;
    float width = 50, height = 50;
    // std::string filepath_;

    uint32_t lifetime_timer_ = SDL_GetTicks();
};

#endif