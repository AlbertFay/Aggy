#include "renderer.h"
#include <iostream>

Renderer::Renderer(const std::size_t screen_height, const std::size_t screen_width, const std::size_t grid_height, const std::size_t grid_width)
    : _screen_height(screen_height),
      _screen_width(screen_width),
      _grid_height(grid_height),
      _grid_width(grid_width) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL_INIT_VIDEO failed to initialize" << std::endl;
  }

  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    std::cout << "IMG_Init did not initialize" << std:: endl;
    std::cout << "Error code: " << IMG_GetError();
  }

  // Initialize SDL Window
  sdl_window = SDL_CreateWindow("Aggy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_height, _screen_width, SDL_WINDOW_SHOWN);
  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  std::cout << "SDL is initialized" << "\n";

  // Initialize SDL Renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

}
Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyRenderer(sdl_renderer);
  
  IMG_Quit();
  SDL_Quit();
}

/*SDL_Texture* Renderer::LoadTexture(std::string path) {
  
  SDL_Texture* texture = NULL;

  SDL_Surface* surface = IMG_Load(path.c_str());
  if(surface == NULL) {
    std::cerr << "Image Load Error" << std::endl;
  }

  texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  if(texture == NULL) {
    std::cerr << "Create Texture Error" << std::endl;
  }

  SDL_FreeSurface(surface);
  
  return texture;
}

void Renderer::DrawTexture(SDL_Texture* texture) {
  SDL_RenderCopy(sdl_renderer, texture, NULL, NULL);
} */

// Draw the objects to the window
void Renderer::Render(Character &character) {
  //Render Character
  SDL_Rect block;
  block.w = character.width;
  block.h = character.height;
  block.x = character.pos_x;
  block.y = character. pos_y;

  SDL_Texture* tex;
  SDL_Surface* surface;
  surface = IMG_Load("C:/C++ Development/C++ Projects/Aggy/Resources/Images/wizard_shooting.png");
  if (surface == NULL){
    std::cerr << "surface did not get created" << std::endl;
  }
  tex = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  if (tex == NULL){
    std::cerr << "Texture did not get created" << std::endl;
  }
  SDL_FreeSurface(surface); 

  //character.SetTexture(sdl_renderer);


  SDL_SetRenderDrawColor(sdl_renderer, 90, 90, 90, 255);
  SDL_RenderClear(sdl_renderer);

  //SDL_RenderCopy(sdl_renderer, tex, NULL, &block);
  SDL_RenderCopyEx(sdl_renderer, tex, NULL, &block, character.angle, NULL, SDL_FLIP_NONE);

  SDL_SetRenderDrawColor(sdl_renderer, 70, 215, 50, 255);
  //SDL_RenderFillRect(sdl_renderer, &block);
  SDL_RenderPresent(sdl_renderer);

}

// Updates the Window title to show updated score and fps
void Renderer::UpdateWindowTitle() {
}