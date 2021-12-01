#include "collision-manager.h"
#include <stdlib.h>

//Is the collision manager an abstract class or does it have working functions?

CollisionManager::CollisionManager()
{
    //Collision Manager Class has been created.
}

void CollisionManager::CheckCollisions(Character &character, GameMap &map)
{
    character.SetXCollisionSpeed(1);
    character.SetYCollisionSpeed(1);
    //Iterate through all the game tiles and check if they are solid (meaning they are collidable)
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (map.array[i][j].solidForCharacter == true)
            {

                //Checking if there is a collision using AABB collision detection
                if (character.hitBox_.x + character.hitBox_.w >= map.array[i][j].GetX() &&
                    map.array[i][j].GetX() + map.array[i][j].GetSize() >= character.hitBox_.x &&
                    character.hitBox_.y + character.hitBox_.h >= map.array[i][j].GetY() &&
                    map.array[i][j].GetY() + map.array[i][j].GetSize() >= character.hitBox_.y)
                {

                    //Temporary code (this changes the color of the game tile if there is a collision)
                    map.array[i][j].collision_ = true;

                    //Variables needed for calculating character vs block and for setting character
                    //position to the correct spot
                    int centerline = ((map.array[i][j].GetX() + map.array[i][j].GetSize() - map.array[i][j].GetX()) / 2);
                    int characterXCenter = character.hitBox_.x + (character.hitBox_.w / 2);
                    int characterYCenter = character.hitBox_.y + (character.hitBox_.h / 2);
                    int differenceX = (map.array[i][j].GetX() + (map.array[i][j].GetSize() / 2)) - characterXCenter;
                    int differenceY = (map.array[i][j].GetY() + (map.array[i][j].GetSize() / 2)) - characterYCenter;
                    int xspace = centerline + (character.hitBox_.w / 2);
                    int yspace = centerline + (character.hitBox_.h / 2);
                    int xoffset = (map.array[i][j].GetX() + centerline) - characterXCenter;
                    int yoffset = (map.array[i][j].GetY() + centerline) - characterYCenter;

                    //Testing to see if collision is on X-axis
                    if (abs(differenceX) >= abs(differenceY))
                    {
                        //If collision is on left side
                        if (xoffset < 0)
                        {
                            std::cout << "Collision on left Side" << std::endl;
                            character.SetXOffset(-(xspace + xoffset));
                            character.SetXCollisionSpeed(-1);
                        }
                        //Collision is on right side
                        else
                        {
                            character.SetXCollisionSpeed(0);
                            character.SetXOffset(xspace - xoffset);
                        }
                    }
                    //Collision is on Y-axis
                    else
                    {
                        //Collision on top
                        if (yoffset < 0)
                        {
                            character.SetYCollisionSpeed(0);
                            character.SetYOffset(-(yspace + yoffset));
                        }
                        //collision on bottom
                        else
                        {
                            character.SetYCollisionSpeed(-1);
                            character.SetYOffset(yspace - yoffset);
                        }
                    }
                }
                else
                {
                    //No collisions, reset character movement to normal
                    map.array[i][j].collision_ = false;
                }
            }
        }
    }
}

void CollisionManager::CheckCollisions(std::vector<Renderable *> &renderables, GameMap &map)
{
    //For each object in renderables, check for collisions against map tiles
    for (auto object : renderables)
    {
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                if (map.array[i][j].solidForOther == true)
                {
                    //Checking if there is a collision using AABB collision detection
                    if (object->GetX() + object->GetWidth() >= map.array[i][j].GetX() &&
                        map.array[i][j].GetX() + map.array[i][j].GetSize() >= object->GetX() &&
                        object->GetY() + object->GetHeight() >= map.array[i][j].GetY() &&
                        map.array[i][j].GetY() + map.array[i][j].GetSize() >= object->GetY())
                    {
                        //Destroy fireball and cause damage to map tile
                        object->Died();
                        map.array[i][j].health_ = map.array[i][j].health_ - 1;
                        if (map.array[i][j].health_ <= 0)
                        {
                            map.array[i][j].destroyed = true;
                        }
                    }
                    else
                    {
                        //This isn't currently implemented
                        //map.array[i][j].collision_ = false;
                    }
                }
            }
        }
    }
}

void CollisionManager::CheckCollisions(std::vector<Enemy *> &enemies, GameMap &map)
{
    //Iterate through all the game tiles and check if they are solid (meaning they are collidable)
    for (auto enemies : enemies){
        enemies->SetXCollisionSpeed(1);
        enemies->SetYCollisionSpeed(1);
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                if (map.array[i][j].solidForOther == true)
                {

                    //Checking if there is a collision using AABB collision detection
                    if (enemies->GetX() + enemies->GetWidth() >= map.array[i][j].GetX() &&
                        map.array[i][j].GetX() + map.array[i][j].GetSize() >= enemies->GetX() &&
                        enemies->GetY() + enemies->GetHeight() >= map.array[i][j].GetY() &&
                        map.array[i][j].GetY() + map.array[i][j].GetSize() >= enemies->GetY())
                    {

                        //Temporary code (this changes the color of the game tile if there is a collision)
                        map.array[i][j].collision_ = true;

                        //Variables needed for calculating enemies vs block and for setting enemies
                        //position to the correct spot
                        int centerline = ((map.array[i][j].GetX() + map.array[i][j].GetSize() - map.array[i][j].GetX()) / 2);
                        int enemiesXCenter = enemies->GetX() + (enemies->GetWidth() / 2);
                        int enemiesYCenter = enemies->GetY() + (enemies->GetWidth() / 2);
                        int differenceX = (map.array[i][j].GetX() + (map.array[i][j].GetSize() / 2)) - enemiesXCenter;
                        int differenceY = (map.array[i][j].GetY() + (map.array[i][j].GetSize() / 2)) - enemiesYCenter;
                        int xspace = centerline + (enemies->GetWidth() / 2);
                        int yspace = centerline + (enemies->GetHeight() / 2);
                        int xoffset = (map.array[i][j].GetX() + centerline) - enemiesXCenter;
                        int yoffset = (map.array[i][j].GetY() + centerline) - enemiesYCenter;

                        //Testing to see if collision is on X-axis
                        if (abs(differenceX) >= abs(differenceY))
                        {
                            //If collision is on left side
                            if (xoffset < 0)
                            {
                                enemies->SetXCollisionSpeed(-1);
                                enemies->SetXOffset(-(xspace + xoffset));
                            }
                            //Collision is on right side
                            else
                            {
                                enemies->SetXCollisionSpeed(0);
                                enemies->SetXOffset(xspace - xoffset);
                            }
                        }
                        //Collision is on Y-axis
                        else
                        {
                            //Collision on top
                            if (yoffset < 0)
                            {
                                enemies->SetYCollisionSpeed(0);
                                enemies->SetYOffset(-(yspace + yoffset));
                            }
                            //collision on bottom
                            else
                            {
                                enemies->SetYCollisionSpeed(-1);
                                enemies->SetYOffset(yspace - yoffset);
                            }
                        }
                    }
                    else
                    {
                        //No collisions, reset enemies movement to normal
                        map.array[i][j].collision_ = false;
                    }
                }
            }
        }
    }
};

void CollisionManager::CheckCollisions(std::vector<Enemy*> &enemies, std::vector<Renderable*> &renderables) {
    for(auto enemy: enemies){
        for(auto renderable: renderables){
            //Checking if there is a collision using AABB collision detection
            if (enemy->GetX() + enemy->GetWidth() >= renderable->GetX() &&
                renderable->GetX() + renderable->GetWidth() >= enemy->GetX() &&
                enemy->GetY() + enemy->GetHeight() >= renderable->GetY() &&
                renderable->GetY() + renderable->GetHeight() >= enemy->GetY()) {

                    //Destroy fireball and create damage to enemy
                    renderable->Died();
                    enemy->TakeDamage(1);
                    if(enemy->GetHealth() <= 0){
                        enemy->Died();
                    }
            }
        }
    }
};

void CollisionManager::CheckCollisions(std::vector<Enemy*> &enemies, Character &character){
    for(auto enemy: enemies){
        //Checking if there is a collision using AABB collision detection
        if (enemy->GetX() + enemy->GetWidth() >= character.hitBox_.x &&
            character.hitBox_.x + character.hitBox_.w >= enemy->GetX() &&
            enemy->GetY() + enemy->GetHeight() >= character.hitBox_.y &&
            character.hitBox_.y + character.hitBox_.h >= enemy->GetY()) {

                //Stop flipping ghost around like crazy
                //Have character take damage
                //Check to see if character died
                character.TakeDamage(enemy->GiveDamage());
            }
    }
};