#include "controller.h"

#include <iostream>

void Controller::ChangeDirection()
{
}

void Controller::HandleInput(Character &character, bool &running)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    character.mousex = x;
    character.mousey = y;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            running = false;
        }
    }
    if(mousestate.button == SDL_BUTTON_LEFT){
    std::cout << "Mouse button left has been pressed" << std::endl;   
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
            running = false;
        }

        if (keystate[SDL_SCANCODE_Q]){
            character.Update(Character::Direction::kRotateLeft);
        }

        if (keystate[SDL_SCANCODE_E]){
            character.Update(Character::Direction::kRotateRight);
        }

        if (keystate [SDL_BUTTON_LEFT]) {
            std::cout << "Mouse button left has been pressed" << std::endl;
            character.Shoot();
        }
        else{
            character.Update();
        }
    }
}

void Controller::MenuInput(bool &running){
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            running = false;
        }
        else if (e.type == SDL_KEYDOWN){
            //this is key being pressed down
            switch (e.key.keysym.sym) {
                
                case SDLK_ESCAPE:
                std::cout << "Escape key is pressed" << "\n";
                running = false;
                break;
            }
            
        }
    }
};