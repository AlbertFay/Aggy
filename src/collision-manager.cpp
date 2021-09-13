#include "collision-manager.h"
#include <stdlib.h>

//Is the collision manager an abstract class or does it have working functions?

CollisionManager::CollisionManager() {
    //Collision Manager Class has been created.
}

void CollisionManager::CheckCollisions(Character &character, GameMap &map) {
    //Iterate through all the game tiles and check if they are solid (meaning they are collidable)
   for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            if (map.array[i][j].solid_ == true){

                //Checking if there is a collision using AABB collision detection
                if(character.GetX() + character.GetWidth() >= map.array[i][j].GetX() &&
                   map.array[i][j].GetX() + map.array[i][j].GetSize() >= character.GetX() &&
                   character.GetY() + character.GetHeight() >= map.array[i][j].GetY() &&
                   map.array[i][j].GetY() + map.array[i][j].GetSize() >= character.GetY()) {

                    //Temporary code (this changes the color of the game tile if there is a collision)  
                    map.array[i][j].collision_ = true;

                    //Variables needed for calculating character vs block and for setting character
                    //position to the correct spot
                    int centerline = ((map.array[i][j].GetX() + map.array[i][j].GetSize() - map.array[i][j].GetX())/2);
                    int characterXCenter = character.GetX() + (character.GetWidth() / 2);
                    int characterYCenter = character.GetY() + (character.GetWidth() / 2);
                    int differenceX = (map.array[i][j].GetX() + (map.array[i][j].GetSize() / 2)) - characterXCenter;
                    int differenceY = (map.array[i][j].GetY() + (map.array[i][j].GetSize() / 2)) - characterYCenter;
                    int xspace = centerline + (character.GetWidth()/2);
                    int yspace = centerline + (character.GetHeight()/2);
                    int xoffset = (map.array[i][j].GetX() + centerline)-characterXCenter;
                    int yoffset = (map.array[i][j].GetY() + centerline)-characterYCenter;

                    //Testing to see if collision is on X-axis
                    if(abs(differenceX) >= abs (differenceY)){
                        //If collision is on left side
                        if(xoffset < 0) {
                            character.SetXCollisionSpeed(-1);
                            character.SetXOffset(-(xspace + xoffset));
                        }
                        //Collision is on right side
                        else {
                            character.SetXCollisionSpeed(0);
                            character.SetXOffset(xspace - xoffset);
                        }
                    }
                    //Collision is on Y-axis
                    else{
                        //Collision on top
                        if(yoffset < 0) {
                            character.SetYCollisionSpeed(0);
                            character.SetYOffset(-(yspace + yoffset));
                        }
                        //collision on bottom
                        else {
                            character.SetYCollisionSpeed(-1);
                            character.SetYOffset(yspace - yoffset);
                        }
                    }
                }
                else{
                    //No collisions, reset character movement to normal
                    map.array[i][j].collision_ = false;
                    character.SetXCollisionSpeed(1);
                    character.SetYCollisionSpeed(1);
                }
            }
        }
    }
}

void CollisionManager::CheckCollisions(std::vector<Renderable*> &renderables, GameMap &map){
    //For each object in renderables, check for collisions against map tiles
    for(auto object: renderables){
        for(int i = 0; i < 16; i++) {
            for(int j = 0; j < 16; j++) {
                if (map.array[i][j].solid_ == true){
                    //Checking if there is a collision using AABB collision detection
                    if(object->GetX() + object->GetWidth() >= map.array[i][j].GetX() &&
                        map.array[i][j].GetX() + map.array[i][j].GetSize() >= object->GetX() &&
                        object->GetY() + object->GetHeight() >= map.array[i][j].GetY() &&
                        map.array[i][j].GetY() + map.array[i][j].GetSize() >= object->GetY()) {
                           //Destroy fireball and cause damage to map tile
                           object->Died();
                           map.array[i][j].health_ = map.array[i][j].health_ - 1; 
                           if(map.array[i][j].health_ <= 0){
                               map.array[i][j].destroyed = true;
                           }
                    }
                    else{
                    //This isn't currently implemented
                    //map.array[i][j].collision_ = false;
                    }
                }
            }
        }
    }
}