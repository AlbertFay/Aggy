#include "controller.h"

#include <iostream>
#include <thread>

/**
 * Controls character and game by taking in keyboard
 * and mouse inputs and updating the character and game
 */
std::vector<std::unique_ptr<Renderable>>&& Controller::HandleInput(Character &character, bool &running, std::vector<std::unique_ptr<Renderable>> &&FiredShots, bool &pause)
{
    //character.SetSpeed(character.defaultspeed);
    int x, y;
    SDL_GetMouseState(&x, &y);
    character.mousex = x;
    character.mousey = y;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            running = false;
        }
        
        if(sdlEvent.button.button == SDL_BUTTON_LEFT){
            buttonRelease_ = false;
            leftMouseButton_ = true;
        }

        if(sdlEvent.button.type == SDL_MOUSEBUTTONUP){
            buttonRelease_ = true;
            leftMouseButton_ = false;
        }
        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE){
            pause = true;
            std::cout << "Escape pressed?" << std::endl;
            SDL_PumpEvents();
            SDL_FlushEvent(SDLK_ESCAPE);
        }
        
    }



    if (SDL_WasInit(SDL_INIT_VIDEO) != 0)
    {
        keystate = SDL_GetKeyboardState(NULL);
        //continuous-response keys
        if (keystate[SDL_SCANCODE_A])
        {
            character.Update(Character::Direction::kLeft);
        }
        if (keystate[SDL_SCANCODE_D])
        {
            character.Update(Character::Direction::kRight);
        }
        if (keystate[SDL_SCANCODE_W])
        {
            character.Update(Character::Direction::kUp);
        }
        if (keystate[SDL_SCANCODE_S])
        {
            character.Update(Character::Direction::kDown);
        }
        if (keystate[SDL_SCANCODE_ESCAPE]){
            /* SDL_FlushEvent(SDL_SCANCODE_ESCAPE);
            pause = true; */
        }

        if (keystate[SDL_SCANCODE_Q]){
            character.Update(Character::Direction::kRotateLeft);
        }

        if (keystate[SDL_SCANCODE_E]){
            character.Update(Character::Direction::kRotateRight);
        }

        if (keystate[SDL_SCANCODE_LSHIFT]){
            character.Sprint(3);
        }
        if (!keystate[SDL_SCANCODE_LSHIFT]){
            character.SetSpeed(character.defaultspeed);
        }

        //BE SURE TO REMOVE THIS WHEN DONE
        if(keystate[SDL_SCANCODE_F1]){
            character.health_ = 0;
        }

        if(leftMouseButton_ ==  true && buttonRelease_ == false){ 
            character.Shoot(std::move(FiredShots));
            character.Update();
        }
        else{
            character.Update();
        }
    }
    return std::move(FiredShots);
};

/**
 * Handles keyboard and mouse inputs while in a menu
 */
void Controller::MenuInput(bool &running, std::vector<Renderer::MenuBoxes> &boxes){
    //Create an event and poll event
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            running = false;
        }
        // If left mouse button is clicked
        if(e.button.button == SDL_BUTTON_LEFT && e.button.type == SDL_MOUSEBUTTONDOWN){
            for(auto &box: boxes){
                if(box.collision_ == true){
                    box.boxClicked_ = true;
                }
            }
        }
        // This section checks for keyboard inputs
        else if (e.type == SDL_KEYDOWN){
            //this is key being pressed down
            switch (e.key.keysym.sym) {
                
                //Currently Unused
                case SDLK_ESCAPE:
                // running = false;
                break;
            }
            
        }
    }
};

/**
 * Determines what each menu box does for the End Menu
 */
std::vector<std::unique_ptr<Renderable>>&& Controller::EndMenuFunctions(std::vector<Renderer::MenuBoxes> &boxes, Character &character, std::vector<std::shared_ptr<Enemy>> &enemies, std::vector<std::unique_ptr<Renderable>> &&FiredShots, GameMap &map, bool &running){
    // Box[0] "Play Again"
    if(boxes[0].boxClicked_){
        //Reset Game
        character.Reset();
        enemies.clear();
        FiredShots.clear();
        boxes[0].boxClicked_ = false;
        map.LoadMap("../maps/map.txt");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    // Box[1] "Quit"
    if(boxes[1].boxClicked_){
        //Stops the game loop and closes application
        running = false;
    }
    return std::move(FiredShots); 
};


void Controller::StartMenu(bool &running, bool &startMenu, bool &allowControl){
SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            running = false;
        }

        if (sdlEvent.type == SDL_KEYDOWN && allowControl){
            startMenu = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

};

void Controller::PauseMenu(bool &running, bool &pause){
    SDL_Event sdlEvent;
    //SDL_FlushEvents(SDLK_ESCAPE, SDL_SCANCODE_ESCAPE);
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            running = false;
        }

        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE){
            pause = false;
        }
    }
};