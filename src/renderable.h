#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "SDL2/SDL.h"

class Renderable {
  public:
    virtual ~Renderable() = default;
    virtual void Update() = 0;
    virtual void RenderRenderable(SDL_Renderer* renderer) = 0;
    virtual bool Exists() = 0;
};

#endif