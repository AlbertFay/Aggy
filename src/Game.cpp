#include "game.h"
#include <thread>
#include "pthread.h"

Game::Game(int number):_number(number){
    std::cout << "The game object has been constructed" << std::endl;
}

void Game::Run(Renderer &renderer, Controller &controller, float FPS, ResourceManager &resources){
    uint32_t title_timestamp = SDL_GetTicks();
    uint32_t frame_start, frame_end, frame_duration;
    int frame_count = 0;
    bool running = true;

    std::vector<Renderable*> renderables;
    std::vector<Enemy*> enemies;
    Character character(renderables);
    SDL_Renderer *pointToRenderer = renderer.GetRenderer();
    CollisionManager collisions;
    Level level;
    
    std::thread t1([&renderer, &resources](){
        renderer.LoadUI(resources);
        std::cout << "T1 has finished" << std::endl;
    });
    
    std::thread t2([&character, &pointToRenderer, &resources](){
        character.LoadResources(pointToRenderer, resources);
        std::cout << "T2 has finished" << std::endl;
    });
    std::thread t3([&renderer, &resources](){
        renderer.LoadEndMenuResources(resources);
        std::cout << "T3 has finished" << std::endl;
    });
    std::thread t4([&collisions, &pointToRenderer, &resources](){
        collisions.LoadResources(pointToRenderer, resources);
    });
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    
    GameMap gamemap(resources);
    
    while (running) {
        frame_start = SDL_GetTicks();
        
        //level.SpawnEnemies(enemies);


        //Update renderables
        for (int i = 0; i < enemies.size();) {
            if (enemies[i]->Exists()){
               enemies[i]->Update(character.GetX(), character.GetY());
               i++;
            }
            else {
                character.score += enemies[i]->GivePoints();
                std::cout << "Character Score: "<< character.score << std::endl;
                delete enemies[i];
                enemies.erase(enemies.begin()+i); 
            }
        }

        //Update enemies
        for (int i = 0; i < renderables.size();) {
            if (renderables[i]->Exists()){
               renderables[i]->Update();
               i++;
            }
            else {
                delete renderables[i];
                renderables.erase(renderables.begin()+i); 
            }
        }

        //Input and Update Character
        controller.HandleInput(character, running);

        //Test for all collisions
        collisions.CheckCollisions(character, gamemap);
        collisions.CheckCollisions(renderables, gamemap);
        collisions.CheckCollisions(enemies, gamemap);
        collisions.CheckCollisions(enemies, renderables);
        collisions.CheckCollisions(enemies, character);
        
        //Render
        renderer.Render(character, renderables, enemies, resources, gamemap);

        frame_end = SDL_GetTicks();

        while(!character.IsAlive() && running == true){
            renderer.EndMenu(resources);
            controller.MenuInput(running);
        }

        // Keep track of how long each loop through Input/Update/Render cycles takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update title screen
        if(frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle();
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for the frame is too small, delay loop until
        // frame will achieve correct frame duration.
        if (frame_duration < FPS) {
            SDL_Delay(FPS - frame_duration);
        }

    }
    //std::cout << "std::vector<Renderable>.size() == " << renderables.size() << std::endl;
    for (int i = 0; i < renderables.size();) {
        //std::cout << "Deleting renderable" << std::endl;
        delete renderables[i];
        //std::cout << "Removing renderable from vector" << std::endl;
        renderables.erase(renderables.begin()+i); 
    }

    for (int i = 0; i < enemies.size();) {
        //std::cout << "Deleting enemies" << std::endl;
        delete enemies[i];
        //std::cout << "Removing enemy pointer from vector" << std::endl;
        enemies.erase(enemies.begin()+i); 
    }

}