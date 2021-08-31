#include "collision-manager.h"
#include <stdlib.h>

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

                    //Test if collision is on x axis or y axis

                    int centerline = ((map.array[i][j].GetX() + map.array[i][j].GetSize() - map.array[i][j].GetX())/2);
                    int differenceX = map.array[i][j].GetX() - character.GetX();
                    int differenceY = map.array[i][j].GetY() - character.GetY();
                    int space = centerline + (character.GetWidth()/2) + 1;
                    int xoffset = (map.array[i][j].GetX() + centerline)-(character.GetX() + (character.GetWidth() / 2));
                    std::cout << "offset: " << xoffset << std::endl;
                    std::cout << "centerline: " << centerline << std::endl;
                    std::cout << "differenceX: " << differenceX << std::endl;
                    std::cout << "differenceY: " << differenceY << std::endl;

                    if(abs(differenceX) >= abs (differenceY)){
                        std::cout << "Collision on x-axis" << std::endl;
                        //collision is on x axis
                        character.SetXCollisionSpeed(0);
                        character.SetXOffset(xoffset - space);
                    }
                    else{
                        std::cout << "Collision on y-axis" << std::endl;
                        character.SetYCollisionSpeed(0);
                        character.SetYOffset(differenceY - centerline);
                    }
                }
                else{
                    map.array[i][j].collision_ = false;
                    character.SetXCollisionSpeed(1);
                    character.SetYCollisionSpeed(1);
                }
            }
        }
    }
}