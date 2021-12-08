# Aggy
 Final Project for Udacity C++ Course. The wizarding demo is a minigame will be a game developed with SDL2 on Windows 10.
 The game will have a main character that will move with W,A,S,D and points and shoots with the mouse.
 Enemies will periodically follow the character and the character will have to survive as long as possible.

 Main.cpp will run the file as well as create necessary objects, it will pass those objects to game.cpp.
 Game.cpp takes care of the game loop and calling all necessary files during each loop as well as controlling framerate.
 Renderer.cpp will initialize the window and be responsible for ultimately everything that is displayed to the screen.
 Controller.cpp will handle all user input and send necessary updates to the playable character object
 Gamemap.cpp loads the background texture and grid.
 Ghost.cpp is inherates from enemy.h which inherates from renderable.h
 Shotfired.cpp inherates from renderable.cpp


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_image >= 2.0.5
  * Installation can be found [here](https://www.libsdl.org/projects/SDL_image/)
* SDL2_ttf >= 2.0.15
  * Installation can be found [here](https://www.libsdl.org/projects/SDL_ttf/)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `.\aggy`.

## Rubric Points covered

* Loops, Functions, I/O
  1. The project demonstrates an understandings of C++ functions and control structures.
    - The whole project?
  2. The project reads datat from a file and processes the data, or the program writes data to a file.
    - gamemap.cpp Gamemap::LoadMap line-19: Takes input from text file and sets background tiles for game
  3. The project accepts user input and processes the input.
    - controller.cpp: THe whole file is for taking in keyboard and mouse inputs from user and moves character in game
* Object Oriented Programming
  1. The project uses Object Oriented Programming techniques.
    - The whole Project?
  2. Classes use appropriate access specifiers for class members.
  3. Class constructors utilize member initialization lists.
  4. Classes abstract implementation details from their interfaces.
  5. Classes encapsulate behavior
  6. Classes follow an appropriate ineritance hierarchy.
  7. Overloaded functions allow the same function to operate on different parameters.
  8. Derived class functions override virtual base class functions.
* Memory Management
  1. The project makes use of references in function declarations.
  2. The project uses destructors appropriately.
  3. The project follows the Rule of 5.
  4. The project uses smart pointers instead of raw pointers.
* Concurrency
  1. The project uses multithreading.
  2. A mutex or lock is used in the project 