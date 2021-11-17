#include "renderer.h"
#include <iostream>

Renderer::Renderer(const std::size_t screen_height, const std::size_t screen_width, const std::size_t grid_height, const std::size_t grid_width)
    : _screen_height(screen_height),
      _screen_width(screen_width),
      _grid_height(grid_height),
      _grid_width(grid_width)
{

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "SDL_INIT_VIDEO failed to initialize" << std::endl;
  }

  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
  {
    std::cout << "IMG_Init did not initialize" << std::endl;
    std::cout << "Error code: " << IMG_GetError();
  }

  if (TTF_Init() < 0)
  {
    std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
  }

  // Initialize SDL Window
  sdl_window = SDL_CreateWindow("Aggy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_height, _screen_width, SDL_WINDOW_SHOWN);
  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  std::cout << "SDL is initialized"
            << "\n";

  // Initialize SDL Renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create UI Dimensions

  //Calculate placement of score
  double percent = screen_height / 100;
  score_rect_.w = 20*percent;
  score_rect_.h = 10*percent;
  score_rect_.x = (45*percent) - (score_rect_.w /2);
  score_rect_.y = (4*percent) - (score_rect_.h /2);

  health_bar_outline_.w = 256;
  health_bar_outline_.h = 32;
  health_bar_outline_.x = 50;
  health_bar_outline_.y = 25;

  digit_rect_.w = 4*percent;
  digit_rect_.h = 10*percent;
  digit_rect_.y = score_rect_.y = (4*percent) - (score_rect_.h /2);
  
}
Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyRenderer(sdl_renderer);

  IMG_Quit();
  SDL_Quit();
}

// Draw the objects to the window
void Renderer::Render(Character &character, std::vector<Renderable *> renderables, std::vector<Enemy *> enemies, ResourceManager &resources, GameMap &gamemap)
{

  // Clear the Render and change color of background
  SDL_SetRenderDrawColor(sdl_renderer, 90, 90, 90, 255);
  SDL_RenderClear(sdl_renderer);
  gamemap.RenderMap(sdl_renderer);

  //Render the character
  character.Render(sdl_renderer, resources);

  for (auto renderable : renderables)
  {
    renderable->RenderRenderable(sdl_renderer, resources);
  }
  for (auto enemies : enemies)
  {
    enemies->RenderRenderable(sdl_renderer, resources);
  }

  RenderUI(resources, character);

  // Display the Render onto the screen; Update Frame
  SDL_RenderPresent(sdl_renderer);
}

SDL_Renderer *Renderer::GetRenderer()
{
  return sdl_renderer;
}

// Updates the Window title to show updated score and fps
void Renderer::UpdateWindowTitle()
{
}

void Renderer::EndMenu(ResourceManager &resources)
{
  //SDL_RenderClear(sdl_renderer);
  SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(sdl_renderer, 82, 82, 82, 25);
  SDL_Rect menuScreen;
  menuScreen.x = 0;
  menuScreen.y = 0;
  menuScreen.w = 1024;
  menuScreen.h = 1024;

  TTF_Font *Sans = TTF_OpenFont("C:/C++ Development/C++ Projects/Aggy/Fonts/open-sans.ttf", 72);
  if (!Sans)
  {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    // handle error
  }

  SDL_Rect game_over; //create a rect
  game_over.x = 100;  //controls the rect's x coordinate
  game_over.y = 100;  // controls the rect's y coordinte
  game_over.w = 700;  // controls the width of the rect
  game_over.h = 300;  // controls the height of the rect
  SDL_RenderCopy(sdl_renderer, resources.getTexture("Game Over"), NULL, &game_over);

  SDL_Rect your_score; //create a rect
  your_score.x = 150;  //controls the rect's x coordinate
  your_score.y = 0;    // controls the rect's y coordinte
  your_score.w = 400;  // controls the width of the rect
  your_score.h = 100;  // controls the height of the rect
  SDL_RenderCopy(sdl_renderer, resources.getTexture("Your Score: "), NULL, &your_score);

  SDL_RenderFillRect(sdl_renderer, &menuScreen);
  SDL_RenderPresent(sdl_renderer);
};

void Renderer::LoadEndMenuResources(ResourceManager &resources)
{
  SDL_Color white = {255, 255, 255};
  TTF_Font *Sans = TTF_OpenFont("C:/C++ Development/C++ Projects/Aggy/Fonts/open-sans.ttf", 144);
  if (!Sans)
  {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    // handle error
  }
  resources.LoadText(sdl_renderer, "Game Over", Sans, white);
  resources.LoadText(sdl_renderer, ("Your Score: "), Sans, white);
};

void Renderer::LoadUI(ResourceManager &resources){
  SDL_Color white = {255, 255, 255};
  TTF_Font* Sans = TTF_OpenFont("C:/C++ Development/C++ Projects/Aggy/Fonts/open-sans.ttf", 144);
  if(!Sans) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    // handle error
  }
  resources.LoadText(sdl_renderer, ("Score: "), Sans, white);
  resources.LoadTexture(sdl_renderer, ("Health Bar Outline"), "C:/C++ Development/C++ Projects/Aggy/Resources/Images/health bar_outline.png");
  resources.LoadText(sdl_renderer, ("1"), Sans, white);
  resources.LoadText(sdl_renderer, ("2"), Sans, white);
  resources.LoadText(sdl_renderer, ("3"), Sans, white);
  resources.LoadText(sdl_renderer, ("4"), Sans, white);
  resources.LoadText(sdl_renderer, ("5"), Sans, white);
  resources.LoadText(sdl_renderer, ("6"), Sans, white);
  resources.LoadText(sdl_renderer, ("7"), Sans, white);
  resources.LoadText(sdl_renderer, ("8"), Sans, white);
  resources.LoadText(sdl_renderer, ("9"), Sans, white);
  resources.LoadText(sdl_renderer, ("0"), Sans, white);
};

void Renderer::RenderUI(ResourceManager &resources, Character &character){
      //Render health bar
    SDL_Rect health_bar;
    health_bar.w = (252.0 / character.max_health) * character.health_;
    health_bar.h = 28;
    health_bar.x = 52;
    health_bar.y = 27;
    SDL_SetRenderDrawColor(sdl_renderer, 255, 15, 0, 255);
    SDL_RenderFillRect(sdl_renderer, &health_bar);

    //Render Health Bar Outline
    SDL_RenderCopy(sdl_renderer, resources.getTexture("Health Bar Outline"), NULL, &health_bar_outline_);
    //Render Score:
    SDL_RenderCopy(sdl_renderer, resources.getTexture("Score: "), NULL, &score_rect_);
    //Render physical score
    int score = character.score;
    int reversescore = 0;
    std::vector<int> scoredigits;
    while(score >= 10){
      reversescore = score % 10;
      score = score / 10; 
      scoredigits.push_back(reversescore);
    }
    scoredigits.push_back(score);
    int digits = 0;
    while(scoredigits.size() > 0){
      score = scoredigits.back();
      digit_rect_.x = ((score_rect_.x + (score_rect_.w )) + (digits * digit_rect_.w));
      SDL_RenderCopy(sdl_renderer, resources.getTexture(std::to_string(score)), NULL, &digit_rect_);
      digits += 1;
      scoredigits.pop_back();
    }
};