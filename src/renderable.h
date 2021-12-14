#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "SDL2/SDL.h"
#include "resource-manager.h"

/**
 * Virtual class for objects that will need to be rendered
 */
class Renderable {
  public:
    virtual ~Renderable() = default;
    virtual void Update() = 0;
    virtual void RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources) = 0;
    virtual bool Exists() = 0;
    virtual float GetX() = 0;
    virtual float GetY() = 0;
    virtual float GetWidth() = 0;
    virtual float GetHeight() = 0;
    virtual void Died() = 0;
};

#endif