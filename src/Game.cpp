#include "game.h"

Game::Game(int number):_number(number){
    std::cout << "The game object has been constructed" << std::endl;
}

void Game::Run(Renderer &renderer, Controller &controller, float FPS, ResourceManager &resources){
    resources_ = resources;
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
    
    //Textures get loaded in to be used later and often
    //resources.LoadTexture(pointToRenderer, "character", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
    renderer.LoadUI(resources);
    character.LoadResources(pointToRenderer, resources);
    resources.LoadTexture(pointToRenderer, "crate", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/crate.png");
    resources.LoadTexture(pointToRenderer, "stone path", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/stone path.png");
    resources.LoadTexture(pointToRenderer, "ghost sprite sheet", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/ghost sprite sheet.png");
    resources.LoadTexture(pointToRenderer, "grass", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/grass.png");
    resources.LoadTexture(pointToRenderer, "grass_to_water", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/grass_to_water.png");
    resources.LoadTexture(pointToRenderer, "water", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/water.png");
    resources.LoadTexture(pointToRenderer, "shrub", "C:/C++ Development/C++ Projects/Aggy/Resources/Images/shrub.png");
    renderer.LoadEndMenuResources(resources);

    GameMap gamemap(resources);
    
    while (running) {
        frame_start = SDL_GetTicks();
        
        // level.SpawnEnemies(enemies);


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
        std::cout << "Deleting renderable" << std::endl;
        delete renderables[i];
        std::cout << "Removing renderable from vector" << std::endl;
        renderables.erase(renderables.begin()+i); 
    }

    for (int i = 0; i < enemies.size();) {
        std::cout << "Deleting enemies" << std::endl;
        delete enemies[i];
        std::cout << "Removing enemy pointer from vector" << std::endl;
        enemies.erase(enemies.begin()+i); 
    }

}