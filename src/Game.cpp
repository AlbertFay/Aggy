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

        Character character;
        //Input, Update, Render()
        controller.HandleInput(running);
        character.Update();
        renderer.Render(character);

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
}