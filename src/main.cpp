#include "SDL2/SDL.h"
#include "renderer.h"
#include "game.h"
#include "controller.h" 
#include <iostream>

constexpr std::size_t DesiredFramePerSecond = 60;
constexpr std::size_t FramePerSecond = 1000/DesiredFramePerSecond;
constexpr std::size_t kScreenHeight = 600;
constexpr std::size_t kScreenWidth = 600;
constexpr std::size_t kgridHeight = 10;
constexpr std::size_t kgridWidth = 10; 

int main()
{
    int number = 0;
    Renderer renderer(kScreenHeight, kScreenWidth, kgridHeight, kgridWidth);
    Game game(number);
    Controller controller;
    ResourceManager resources;
    game.Run(renderer, controller, FramePerSecond, resources);

    //Terminate game, Then run 
    std::cout << "The object has been terminated, closing Application" << std::endl;
    return 0;
} 