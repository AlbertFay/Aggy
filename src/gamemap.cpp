#include "gamemap.h"


using namespace std;

GameMap::GameMap(ResourceManager &resources): resources_(resources){
    GameMap::LoadMap("C:\\C++ Development\\C++ Projects\\Aggy\\maps\\map.txt");

    //i is columns, j is rows
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            array[i][j].SetSize(GameMap::pixelsize_);
            array[i][j].setX(j * pixelsize_);
            array[i][j].setY(i * pixelsize_);
        }
    }
}

void GameMap::LoadMap(string fileName) {
    ifstream file;
    file.open(fileName);
    string line;
    if(file.is_open()){
            for(int i = 0; i < 16; i++){
                getline(file, line);
                stringstream stream(line);
                while(stream.good()){
                    for(int j = 0; j < 16; j++){
                        string number;
                        getline(stream, number, ',');
                        int num = stoi(number);
                        array[i][j].num_block = num;
                        switch(array[i][j].num_block){
                            case 0:
                            // std::cout << "this is case 0" << endl;
                            array[i][j].blocktype_ = Grid_Space::blockType::nothing;
                            break;

                            case 1:
                            // std::cout << "this is case 1" << endl;
                            array[i][j].blocktype_ = Grid_Space::blockType::stone_path;
                            break;

                            case 2:
                            array[i][j].blocktype_ = Grid_Space::blockType::grass;
                            array[i][j].blocktype2_ = Grid_Space::blockType::crate;
                            array[i][j].solidForCharacter = true;
                            array[i][j].solidForOther = true;
                            array[i][j].health_ = 3;
                            break;

                            case 3:
                            array[i][j].blocktype_ = Grid_Space::blockType::grass;
                            break;

                            case 4:
                            array[i][j].blocktype_ = Grid_Space::blockType::grassToWater1;
                            break;
                            
                            case 5:
                            array[i][j].blocktype_ = Grid_Space::blockType::grassToWater2;
                            break;

                            case 6:
                            array[i][j].blocktype_ = Grid_Space::blockType::water;
                            array[i][j].solidForCharacter = true;
                            break;

                            case 7:
                            array[i][j].blocktype_ = Grid_Space::blockType::shrub1;
                            array[i][j].solidForCharacter = true;
                            break;

                            case 8:
                            array[i][j].blocktype_ = Grid_Space::blockType::grass;
                            array[i][j].blocktype2_ = Grid_Space::blockType::flower1;
                            break;

                            case 9:
                            array[i][j].blocktype_ = Grid_Space::blockType::grass;
                            array[i][j].blocktype2_ = Grid_Space::blockType::flower2;
                            break;

                            case 10:
                            array[i][j].blocktype_ = Grid_Space::blockType::grass;
                            array[i][j].blocktype2_ = Grid_Space::blockType::flower3;
                            break;

                            case 11:
                            array[i][j].blocktype_ = Grid_Space::blockType::shrub2;
                            array[i][j].solidForCharacter = true;
                            break;
                        }
                    }
                }
            }
    }
    else{
        std::cout << "couldnt open file" << endl;
    }
}

void GameMap::RenderMap(SDL_Renderer* renderer) {
    SDL_Rect sprite1;
    SDL_Rect sprite2;
    SDL_Rect sprite3;
    sprite1.x = 0;
    sprite1.y = 0;
    sprite1.w = 64;
    sprite1.h = 64;

    sprite2.x = 64;
    sprite2.y = 0;
    sprite2.w = 64;
    sprite2.h = 64;

    sprite3.x = 128;
    sprite3.y = 0;
    sprite3.w = 64;
    sprite3.h = 64;

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
                array[i][j].blocktype2_ = Grid_Space::blockType::nothing;
                array[i][j].solidForOther = false;
                array[i][j].solidForCharacter = false;
            }

            switch(array[i][j].blocktype_){
                case Grid_Space::blockType::nothing:
                 SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                 SDL_RenderDrawRect(renderer, &gridBlock);
                break;

                case Grid_Space::blockType::stone_path:
                SDL_RenderCopy(renderer, resources_.getTexture("stone path"), NULL, &gridBlock);
                break;

                case Grid_Space::blockType::grass:
                SDL_RenderCopy(renderer, resources_.getTexture("grass"), NULL, &gridBlock);
                break;

                case Grid_Space::blockType::grassToWater1:
                SDL_RenderCopy(renderer, resources_.getTexture("grass_to_water"), &sprite1, &gridBlock);
                break;

                case Grid_Space::blockType::grassToWater2:
                SDL_RenderCopy(renderer, resources_.getTexture("grass_to_water"), &sprite2, &gridBlock);
                break;

                case Grid_Space::blockType::water:
                SDL_RenderCopy(renderer, resources_.getTexture("water"), NULL, &gridBlock);
                break;

                case Grid_Space::blockType::shrub1:
                SDL_RenderCopy(renderer, resources_.getTexture("shrub"), &sprite1, &gridBlock);
                break;

                case Grid_Space::blockType::shrub2:
                SDL_RenderCopy(renderer, resources_.getTexture("shrub"), &sprite2, &gridBlock);
                break;
            }
            switch(array[i][j].blocktype2_){
                case Grid_Space::blockType::flower1:
                SDL_RenderCopy(renderer, resources_.getTexture("flowers"), &sprite1, &gridBlock);
                break;

                case Grid_Space::blockType::flower2:
                SDL_RenderCopy(renderer, resources_.getTexture("flowers"), &sprite2, &gridBlock);
                break;

                case Grid_Space::blockType::flower3:
                SDL_RenderCopy(renderer, resources_.getTexture("flowers"), &sprite3, &gridBlock);
                break;

                case Grid_Space::blockType::crate:
                SDL_RenderCopy(renderer, resources_.getTexture("crate"), NULL, &gridBlock);
                if(array[i][j].collision_){
                    // std::cout << "there is a collision with crate" << std::endl;
                    SDL_RenderCopy(renderer, resources_.getTexture("crate"), NULL, &gridBlock);
                }
                break;
            }
        }
    }
}

void GameMap::Update() {

}