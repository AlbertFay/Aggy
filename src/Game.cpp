#include "game.h"
#include <iostream>

Game::Game(int number):_number(number){
    std::cout << "The game object has been constructed" << std::endl;}

void Game::Run(Renderer &renderer, Controller &controller, float FPS){
    uint32_t title_timestamp = SDL_GetTicks();
    uint32_t frame_start, frame_end, frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running) {
        frame_start = SDL_GetTicks();

        //Input, Update, Render()

        frame_end = SDL_GetTicks();

        frame_count++;
        frame_duration = frame_end - frame_start;
        running = false;
    }
}