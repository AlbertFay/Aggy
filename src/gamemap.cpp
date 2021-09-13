#include "gamemap.h"

GameMap::GameMap(ResourceManager &resources): resources_(resources){
            
            array[5][6].blocktype_ = Grid_Space::blockType::stone_path;
            array[5][7].blocktype_ = Grid_Space::blockType::stone_path;
            array[6][6].blocktype_ = Grid_Space::blockType::stone_path;
            array[6][7].blocktype_ = Grid_Space::blockType::stone_path;
            
            array[2][4].blocktype_ = Grid_Space::blockType::crate;
            array[2][6].blocktype_ = Grid_Space::blockType::crate;
            array[2][7].blocktype_ = Grid_Space::blockType::crate;
            array[8][1].blocktype_ = Grid_Space::blockType::crate;
            array[9][2].blocktype_ = Grid_Space::blockType::crate;
            array[7][1].blocktype_ = Grid_Space::blockType::crate;
    //i is columns, j is rows
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            array[i][j].solid_ = false;
            array[i][j].SetSize(GameMap::pixelsize_);
            array[i][j].setX(j * pixelsize_);
            array[i][j].setY(i * pixelsize_);
            array[i][j].collision_ = false;


            switch(array[i][j].blocktype_){
                case Grid_Space::blockType::crate:
                array[i][j].solid_ = true;
                array[i][j].health_ = 3;
                break;
            }
        }
    }
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

            if (array[i][j].destroyed == true){
                array[i][j].destroyed = false;
                array[i][j].blocktype_ = Grid_Space::blockType::nothing;
                array[i][j].solid_ = false;
            }

            switch(array[i][j].blocktype_){
                case Grid_Space::blockType::nothing:
                 SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                 SDL_RenderDrawRect(renderer, &gridBlock);
                break;

                case Grid_Space::blockType::stone_path:
                SDL_RenderCopy(renderer, resources_.getTexture("stone path"), NULL, &gridBlock);
                break;
                
                case Grid_Space::blockType::crate:
                SDL_RenderCopy(renderer, resources_.getTexture("crate"), NULL, &gridBlock);
                if(array[i][j].collision_){
                    std::cout << "there is a collision with crate" << std::endl;
                    SDL_RenderCopy(renderer, resources_.getTexture("crate"), NULL, &gridBlock);
                }
                break;
            }
            //If non-solid block, draw green
            //else draw red
        }
    }
}

void GameMap::Update() {

}