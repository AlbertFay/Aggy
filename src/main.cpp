#include "SDL2/SDL.h"
#include "renderer.h"
#include "game.h"
#include "controller.h" 
#include <iostream>

constexpr float DesiredFramePerSecond = 60;
constexpr float FramePerSecond = 1000/DesiredFramePerSecond;
constexpr int kScreenHeight = 600;
constexpr int kScreenWidth = 600;
constexpr int kgridHeight = 10;
constexpr int kgridWidth = 10; 

int main()
{
    int number = 0;
    Renderer renderer(kScreenHeight, kScreenWidth, kgridHeight, kgridWidth);
    Game game(number);
    Controller controller;
    game.Run(renderer, controller, FramePerSecond);

    //Terminate game, Then run 
    std::cout << "The object has been terminated, closing Application" << std::endl;
    return 0;
    
} 