#include "controller.h"

#include <iostream>
#include <thread>

void Controller::ChangeDirection()
{
}

std::vector<std::unique_ptr<Renderable>>&& Controller::HandleInput(Character &character, bool &running, std::vector<std::unique_ptr<Renderable>> &&FiredShots)
{
    //character.SetSpeed(character.defaultspeed);
    int x, y;
    SDL_GetMouseState(&x, &y);
    character.mousex = x;
    character.mousey = y;

    SDL_MouseButtonEvent mouseEvent;
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
            // running = false;
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

void Controller::MenuInput(bool &running, std::vector<Renderer::MenuBoxes> &boxes){
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            running = false;
        }
        if(e.button.button == SDL_BUTTON_LEFT && e.button.type == SDL_MOUSEBUTTONDOWN){
            for(auto &box: boxes){
                if(box.collision_ == true){
                    box.boxClicked_ = true;
                    std::cout << "Box has been clicked" << std::endl;
                }
            }
        }
        else if (e.type == SDL_KEYDOWN){
            //this is key being pressed down
            switch (e.key.keysym.sym) {
                
                case SDLK_ESCAPE:
                std::cout << "Escape key is pressed" << "\n";
                // running = false;
                break;
            }
            
        }
    }
};

std::vector<std::unique_ptr<Renderable>>&& Controller::EndMenuFunctions(std::vector<Renderer::MenuBoxes> &boxes, Character &character, std::vector<std::shared_ptr<Enemy>> &enemies, std::vector<std::unique_ptr<Renderable>> &&FiredShots, GameMap &map, bool &running){
    // Box[0] "Play Again"
    if(boxes[0].boxClicked_){
        std::cout << "Does this run part 2" << std::endl;
        //reset game somehow
        character.Reset();
        enemies.clear();
        FiredShots.clear();
        boxes[0].boxClicked_ = false;
        map.LoadMap("C:\\C++ Development\\C++ Projects\\Aggy\\maps\\map.txt");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    // Box[1] "Quit"
    if(boxes[1].boxClicked_){
        running = false;
    }
    return std::move(FiredShots); 
};