#include "game.h"
#include <thread>
#include "pthread.h"
#include "collision-manager.h"

/**
 * Default Constructor for Game object
 */
Game::Game(){
    std::cout << "The game object has been constructed" << std::endl;
}


void Game::Run(Renderer &renderer, Controller &controller, float FPS, ResourceManager &resources){
    //Create variables for keeping track of framerate
    uint32_t title_timestamp = SDL_GetTicks();
    uint32_t frame_start, frame_end, frame_duration;
    int frame_count = 0;
    bool running = true;
    
    // Create vectors of smart pointers
    std::vector<std::unique_ptr<Renderable>> FiredShots;
    std::vector<std::shared_ptr<Enemy>> enemies;

    // Create necessary game objects
    Character character;
    SDL_Renderer *pointToRenderer = renderer.GetRenderer();
    CollisionManager collisions; 
    Level level;
    std::vector<Renderer::MenuBoxes> EndMenuBoxes_;
    std::vector<Renderer::MenuBoxes> pauseMenuBoxes_;

    //Load textures and necessary resources to be used later
    renderer.LoadEndMenuBoxes(EndMenuBoxes_, resources);
    renderer.LoadPauseMenu(pauseMenuBoxes_, resources);
    
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

    /**
     * Create Introduction to page and wait x seconds before
     * player can move on.
     */
    bool startMenu = true;
    bool allowControl = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_ = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::seconds>(start_).time_since_epoch().count();
    while(running == true && startMenu == true){
        std::chrono::time_point<std::chrono::high_resolution_clock> end_ = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::time_point_cast<std::chrono::seconds>(end_).time_since_epoch().count();
        if(end - start > 0){
            allowControl = true;
        }
        controller.StartMenu(running, startMenu, allowControl);
        renderer.StartPage(resources, allowControl);
    }
    
    //Create and load map
    GameMap gamemap(resources);
    
    //Start game loop
    while (running) {
        //keep track of what time the frame starts
        frame_start = SDL_GetTicks();

        while(pause){
            controller.PauseMenu(running, pause, pauseMenuBoxes_);
            collisions.CheckCollisions(pauseMenuBoxes_);
            controller.PauseMenuFunctions(pauseMenuBoxes_, running, pause);
            renderer.PauseMenu(pauseMenuBoxes_, resources);
            //menu screen
        }
        
        //Spawn in enemies
        level.SpawnEnemies(enemies);

        //Update Enemies
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

        //Update renderables or firedshots... both the same thing
        for (int i = 0; i < FiredShots.size();) {
            if (FiredShots[i]->Exists()){
               FiredShots[i]->Update();
               i++;
            }
            else {
                FiredShots.erase(FiredShots.begin()+i);
            }
        }

        //Input and Update Character
        controller.HandleInput(character, running, std::move(FiredShots), pause);

        //Test for all collisions
        collisions.CheckCollisions(character, gamemap);
        collisions.CheckCollisions(std::move(FiredShots), gamemap);
        collisions.CheckCollisions(enemies, gamemap);
        collisions.CheckCollisions(enemies, std::move(FiredShots));
        collisions.CheckCollisions(enemies, character);

        //Render
        renderer.Render(character, std::move(FiredShots), enemies, resources, gamemap);

        // Get time for when frame ends
        frame_end = SDL_GetTicks();

        //Character has died, this starts the Menu for the end of the game
        while(!character.IsAlive() && running == true){
            collisions.CheckCollisions(EndMenuBoxes_);
            controller.MenuInput(running, EndMenuBoxes_);
            controller.EndMenuFunctions(EndMenuBoxes_, character, enemies, std::move(FiredShots), gamemap, running);
            renderer.EndMenu(resources, character.score, EndMenuBoxes_);
        }

        // Keep track of how long each loop through Input/Update/Render cycles takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update title screen
        if(frame_end - title_timestamp >= 1000) {
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