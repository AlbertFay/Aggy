#include "game.h"

Game::Game(int number):_number(number){
    std::cout << "The game object has been constructed" << std::endl;}

void Game::Run(Renderer &renderer, Controller &controller, float FPS, ResourceManager &resources){
    resources_ = resources;
    uint32_t title_timestamp = SDL_GetTicks();
    uint32_t frame_start, frame_end, frame_duration;
    int frame_count = 0;
    bool running = true;

    std::vector<Renderable*> renderables;
    Character character(renderables);
    SDL_Renderer* pointToRenderer = renderer.GetRenderer();
    GameMap gamemap;
    CollisionManager collisions;
    
    //Textures get loaded in to be used later and often
    resources.LoadTexture(pointToRenderer, "character", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
    resources.LoadTexture(pointToRenderer, "fireball", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/red_fireball.png");
    
    while (running) {
        frame_start = SDL_GetTicks();


        //Update renderables
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
        
        //Render
        renderer.Render(character, renderables, resources, gamemap);

        frame_end = SDL_GetTicks();

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

        //running = false;
    }
    std::cout << "std::vector<Renderable>.size() == " << renderables.size() << std::endl;
    for (int i = 0; i < renderables.size();) {
        std::cout << "Deleting renderable" << std::endl;
        delete renderables[i];
        std::cout << "Removing renderable from vector" << std::endl;
        renderables.erase(renderables.begin()+i); 
    }

}