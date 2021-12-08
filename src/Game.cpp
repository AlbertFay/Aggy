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

    std::vector<std::unique_ptr<Renderable>> FiredShots;
    std::vector<std::shared_ptr<Enemy>> enemies;

    Character character;
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
        
        level.SpawnEnemies(enemies);

        //Update renderables
        for (int i = 0; i < enemies.size();) {
            if (enemies[i]->Exists()){
               enemies[i]->Update(character.GetX(), character.GetY());
               i++;
            }
            else {
                character.score += enemies[i]->GivePoints();
                std::cout << "Character Score: "<< character.score << std::endl;
                enemies.erase(enemies.begin()+i); 
            }
        }

        //Update enemies
        for (int i = 0; i < FiredShots.size();) {
            if (FiredShots[i]->Exists()){
               FiredShots[i]->Update();
               i++;
            }
            else {
                //delete FiredShots[i];
                FiredShots.erase(FiredShots.begin()+i);
            }
        }

        //Input and Update Character
        controller.HandleInput(character, running, std::move(FiredShots));

        //Test for all collisions
        collisions.CheckCollisions(character, gamemap);
        collisions.CheckCollisions(std::move(FiredShots), gamemap);
        collisions.CheckCollisions(enemies, gamemap);
        collisions.CheckCollisions(enemies, std::move(FiredShots));
        collisions.CheckCollisions(enemies, character);

        //Render
        renderer.Render(character, std::move(FiredShots), enemies, resources, gamemap);

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
}