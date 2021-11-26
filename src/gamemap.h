#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include "resource-manager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class GameMap {
  public:
  
    struct Grid_Space {
      public:
      enum class blockType {nothing, crate, stone_path, grass, grassToWater1, grassToWater2, water, shrub};
        //TEMP
        bool collision_ = false;
        //TEMP
        bool solidForCharacter = false; 
        bool solidForOther = false;
        float health_;
        bool destroyed = false;
        int num_block = 1;

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
       blockType blocktype_ = blockType::nothing;
      private:
        int pixelsize_;
        int x_;
        int y_;
    };

    GameMap(ResourceManager &resources);
    void LoadMap(std::string fileName); //Intended for loading textures for blocks into map
    void RenderMap(SDL_Renderer* renderer);
    void Update(); //Update to different maps 


    Grid_Space array[16][16];

  private:
    ResourceManager resources_;
    int pixelsize_ = 64;
};

#endif