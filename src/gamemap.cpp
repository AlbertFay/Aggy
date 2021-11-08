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
                            array[i][j].blocktype_ = Grid_Space::blockType::crate;
                            array[i][j].solid_ = true;
                            array[i][j].health_ = 3;
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