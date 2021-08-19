#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class GameMap {
  public:
  
    struct Grid_Space {
      public:
        //TEMP
        bool collision_;
        //TEMP
        bool solid_;  
        int GetSize(){
        return pixelsize_;
        };
        int GetX(){
          return x_;
        };
        int GetY(){
          return y_;
        };
        void SetSize(int size){
          pixelsize_ = size;
        };
        void setX(int x){
          x_ = x;
        }
        void setY(int y){
          y_ = y;
        }
      private:
        int pixelsize_;
        int x_;
        int y_;
    };

    GameMap();
    void LoadMap(); //Intended for loading textures for blocks into map
    void RenderMap(SDL_Renderer* renderer);
    void Update(); //Update to different maps 


    Grid_Space array[7][7];

  private:
    int pixelsize_ = 100;
};

#endif