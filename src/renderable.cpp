#include "renderable.h"
#include <iostream>

bool Renderable::Exists(){
    std::cout << "This needs to be implemented" << std::endl;
    return true;
};

void Renderable::RenderRenderable(SDL_Renderer* renderer, ResourceManager &resources){
    std::cout << "This needs to be implemented" << std::endl;
};

void Renderable::Update() {
    std::cout << "this needs to be implemented" << std:: endl;
};

//void Renderable::Update(int x, int y){};