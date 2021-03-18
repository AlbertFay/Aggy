#include "controller.h"

#include <iostream>

void Controller::ChangeDirection()
{
}

void Controller::HandleInput(Character &character, bool &running, std::vector<Renderable*> &renderables)
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            running = false;
        }
    }


    if (SDL_WasInit(SDL_INIT_VIDEO) != 0)
    {
        keystate = SDL_GetKeyboardState(NULL);
        //continuous-response keys
        if (keystate[SDL_SCANCODE_LEFT])
        {
            std::cout << "Left Key is pressed"
                      << "\n";
            character.Update(Character::Direction::kLeft);
        }
        if (keystate[SDL_SCANCODE_RIGHT])
        {
            std::cout << "Right Key is pressed"
                      << "\n";
            character.Update(Character::Direction::kRight);
        }
        if (keystate[SDL_SCANCODE_UP])
        {
            std::cout << "Up Key is pressed"
                      << "\n";
            character.Update(Character::Direction::kUp);
        }
        if (keystate[SDL_SCANCODE_DOWN])
        {
            std::cout << "Down Key is pressed"
                      << "\n";
            character.Update(Character::Direction::kDown);
        }
        if (keystate[SDL_SCANCODE_ESCAPE]){
            std::cout << "Escape key is pressed" << "\n";
            running = false;
        }

        if (keystate[SDL_SCANCODE_Q]){
            std::cout << "Q key is pressed" << "\n";
            character.Update(Character::Direction::kRotateLeft);
        }

        if (keystate[SDL_SCANCODE_E]){
            std::cout << "E key is pressed" << "\n";
            character.Update(Character::Direction::kRotateRight);
        }

        if (keystate [SDL_SCANCODE_SPACE]) {
            std::cout << "Space key is pressed" << "\n";
            character.Shoot(renderables);
        }
    }
}