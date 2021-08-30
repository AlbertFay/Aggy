#include "gamemap.h"

GameMap::GameMap(){
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            array[i][j].solid_ = false;
            array[i][j].SetSize(GameMap::pixelsize_);
            array[i][j].setX(j * pixelsize_);
            array[i][j].setY(i * pixelsize_);
            array[i][j].collision_ = false;
        }
    }

    array[2][4].solid_ = true;
}

void GameMap::LoadMap() {
    
}

void GameMap::RenderMap(SDL_Renderer* renderer) {
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            
            //Tempory gridlines
            SDL_Rect gridBlock;
            gridBlock.w = pixelsize_;
            gridBlock.h = pixelsize_;
            gridBlock.y = i * pixelsize_;
            gridBlock.x = j * pixelsize_;

            //If non-solid block, draw green
            if(array[i][j].solid_ == false) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderDrawRect(renderer, &gridBlock);
            }
            //else draw red
            else {
                if(array[i][j].collision_){
                    SDL_SetRenderDrawColor(renderer, 150, 0, 135, 255);
                    SDL_RenderDrawRect(renderer, &gridBlock);
                }
                else{
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderDrawRect(renderer, &gridBlock);
                }
            }
        }
    }
}

void GameMap::Update() {

}