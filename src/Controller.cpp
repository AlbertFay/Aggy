#include "controller.h"

#include <iostream>

void Controller::ChangeDirection(){

}

void Controller::HandleInput(bool &running){
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            running = false;
        }
        else if (e.type == SDL_KEYDOWN){
            //this is key being pressed down
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                //change direction or do something
                std::cout << "Up Key is pressed" << "\n";
                break;

                case SDLK_DOWN:
                //Change direction or do something
                std::cout << "Down Key is pressed" << "\n";
                break;

                case SDLK_LEFT:
                //Change direction or do something
                std::cout << "Left Key is pressed" << "\n";
                break;

                case SDLK_RIGHT:
                //Change direction or do something
                std::cout << "Right Key is pressed" << "\n";
                break;

                case SDLK_ESCAPE:
                std::cout << "Escape key is pressed" << "\n";
                running = false;
                break;
            }
            
        }
    }
}