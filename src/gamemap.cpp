#include "gamemap.h"

GameMap::GameMap(){
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            array[i][j].solid_ = false;
        }
    }

    array[2][4].solid_ = true;
}

void GameMap::LoadMap() {
    
}

void GameMap::RenderMap(SDL_Renderer* renderer) {
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            SDL_Rect gridBlock;
            gridBlock.w = pixelsize_;
            gridBlock.h = pixelsize_;
            gridBlock.y = i * pixelsize_;
            gridBlock.x = j * pixelsize_;
            if(array[i][j].solid_ == false) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderDrawRect(renderer, &gridBlock);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &gridBlock);
            }
        }
    }
}

void GameMap::Update() {

}

void GameMap::checkCollision(/*Object such as fireball or character*/) {
    //
}