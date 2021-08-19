#include "collision-manager.h"

//Is the collision manager an abstract class or does it have working functions?

CollisionManager::CollisionManager() {
    //Collision Manager Class has been created.
}

void CollisionManager::CheckCollisions(Character &character, GameMap &map) {
    /*
    *Nested for loop to parse through map blocks
    *
    *If block is solid
    *Check collision on x axis
    *if collision, set character x speed to 0
    *else set character x speed to 1
    *
    *Check collision on y axis
    *if collision, set character y speed to 0
    *else set character x speed to 1
    */
   for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            if (map.array[i][j].solid_ == true){

                //Checking AABB collision
                if(character.GetX() + character.GetWidth() >= map.array[i][j].GetX() &&
                   map.array[i][j].GetX() + map.array[i][j].GetSize() >= character.GetX() &&
                   character.GetY() + character.GetHeight() >= map.array[i][j].GetY() &&
                   map.array[i][j].GetY() + map.array[i][j].GetSize() >= character.GetY()) {
                       
                    //Check to see if collision is closer to x or y, then resolve character just outside
                    //of collision coordinates and set character x or y collision speed to 0;
                    std::cout << "There is a collision between character and grid block" << std::endl;
                    map.array[i][j].collision_ = true;
                }
                else{
                    map.array[i][j].collision_ = false;
                }
            }
        }
    }
}