#include "SDL2/SDL.h"
#include "renderer.h"
#include "game.h"
#include "controller.h" 
#include <iostream>

constexpr std::size_t DesiredFramePerSecond = 60;
constexpr std::size_t FramePerSecond = 1000/DesiredFramePerSecond;
constexpr std::size_t kScreenHeight = 1024;
constexpr std::size_t kScreenWidth = 1024;
constexpr std::size_t kgridHeight = 10;
constexpr std::size_t kgridWidth = 10;  

int main()
{
    //Create Necessary Game objects
    
    Renderer renderer(kScreenHeight, kScreenWidth, kgridHeight, kgridWidth);
    Game game;
    Controller controller;
    ResourceManager resources;

    // Run the game
    game.Run(renderer, controller, FramePerSecond, resources);

    std::cout << "The object has been terminated, closing Application" << std::endl;
    return 0;
} 