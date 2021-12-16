#include "renderer.h"
#include <iostream>

/**
 * Constructor for Renderer. Initializes SDL components and sets
 * UI Placements.
 */
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
    // Initialize SDL_Image
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cout << "IMG_Init did not initialize" << std::endl;
        std::cout << "Error code: " << IMG_GetError();
    }
    // Initialize SDL_TTF
    if (TTF_Init() < 0)
    {
        std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
    }

    // Initialize SDL Window
    sdl_window = SDL_CreateWindow("Wizard Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_height, _screen_width, SDL_WINDOW_SHOWN);
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

    // Set UI placements

    // Placement of score
    double percent = screen_height / 100;
    score_rect_.w = 20 * percent;
    score_rect_.h = 10 * percent;
    score_rect_.x = (45 * percent) - (score_rect_.w / 2);
    score_rect_.y = (4 * percent) - (score_rect_.h / 2);

    // Placement for health_bar_outline
    health_bar_outline_.w = 256;
    health_bar_outline_.h = 32;
    health_bar_outline_.x = (5 * percent);
    health_bar_outline_.y = (2.5 * percent);

    // Placement for energy_bar_outline
    energy_bar_outline_.w = 256;
    energy_bar_outline_.h = 32;
    energy_bar_outline_.x = (5 * percent);
    energy_bar_outline_.y = (6 * percent);

    // Placement for where each digit of the score goes
    digit_rect_.w = 4 * percent;
    digit_rect_.h = 10 * percent;
    digit_rect_.y = score_rect_.y;
}
Renderer::~Renderer()
{
    SDL_DestroyWindow(sdl_window);
    SDL_DestroyRenderer(sdl_renderer);

    IMG_Quit();
    SDL_Quit();
}

/**
 * Calls objects to Render by passing SDL_renderer& to objects
 * then renders UI
 */
std::vector<std::unique_ptr<Renderable>> &&Renderer::Render(Character &character, std::vector<std::unique_ptr<Renderable>> &&firedShot, std::vector<std::shared_ptr<Enemy>> &enemies, ResourceManager &resources, GameMap &gamemap)
{

    // Clear the Render and change color of background
    SDL_SetRenderDrawColor(sdl_renderer, 90, 90, 90, 255);
    SDL_RenderClear(sdl_renderer);
    gamemap.RenderMap(sdl_renderer);

    //Render the character
    character.Render(sdl_renderer, resources);

    for (auto &renderable : firedShot)
    {
        renderable->RenderRenderable(sdl_renderer, resources);
    }
    for (auto &enemies : enemies)
    {
        enemies->RenderRenderable(sdl_renderer, resources);
    }

    RenderUI(resources, character);

    // Display the Render onto the screen; Update Frame
    SDL_RenderPresent(sdl_renderer);
    // return std::move(FiredShots);
    return std::move(firedShot);
};

/**
 * Returns a pointer to the SDL_Renderer object created
 * by the Renderer class.
 */
SDL_Renderer *Renderer::GetRenderer()
{
    return sdl_renderer;
}

/**
 * Renders everything for the End Menu
 */
void Renderer::EndMenu(ResourceManager &resources, int score, std::vector<MenuBoxes> &menuBoxes)
{
    //SDL_RenderClear(sdl_renderer);
    SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(sdl_renderer, 82, 82, 82, 25);
    SDL_Rect menuScreen;
    menuScreen.x = 0;
    menuScreen.y = 0;
    menuScreen.w = 1024;
    menuScreen.h = 1024;

    TTF_Font *Sans = TTF_OpenFont("../Fonts/open-sans.ttf", 72);
    if (!Sans)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }

    double percent = 1024 / 100;

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

    digit_rect_.w = 4 * percent;
    digit_rect_.h = your_score.h;
    digit_rect_.y = your_score.y;

    int reversescore = 0;
    std::vector<int> scoredigits;
    while (score >= 10)
    {
        reversescore = score % 10;
        score = score / 10;
        scoredigits.push_back(reversescore);
    }
    scoredigits.push_back(score);
    int digits = 0;
    while (scoredigits.size() > 0)
    {
        score = scoredigits.back();
        digit_rect_.x = ((your_score.x + (your_score.w)) + (digits * digit_rect_.w));
        SDL_RenderCopy(sdl_renderer, resources.getTexture(std::to_string(score)), NULL, &digit_rect_);
        digits += 1;
        scoredigits.pop_back();
    }

    SDL_RenderFillRect(sdl_renderer, &menuScreen);
    //**********************************************************************************************************************************************
    SDL_SetRenderDrawColor(sdl_renderer, 15, 15, 255, 255);
    if (menuBoxes[0].collision_ == true)
    {
        SDL_RenderFillRect(sdl_renderer, &(menuBoxes[0].box_));
        SDL_RenderCopy(sdl_renderer, resources.getTexture("Play Again"), NULL, &menuBoxes[0].box_);
    }
    else
    {
        SDL_RenderDrawRect(sdl_renderer, &(menuBoxes[0].box_));
        SDL_RenderCopy(sdl_renderer, resources.getTexture("Play Again"), NULL, &menuBoxes[0].box_);
    }

    SDL_SetRenderDrawColor(sdl_renderer, 255, 15, 15, 255);
    if (menuBoxes[1].collision_ == true)
    {
        SDL_RenderFillRect(sdl_renderer, &(menuBoxes[1].box_));
        SDL_RenderCopy(sdl_renderer, resources.getTexture("  Quit  "), NULL, &menuBoxes[1].box_);
    }
    else
    {
        SDL_RenderDrawRect(sdl_renderer, &(menuBoxes[1].box_));
        SDL_RenderCopy(sdl_renderer, resources.getTexture("  Quit  "), NULL, &menuBoxes[1].box_);
    }
    //**********************************************************************************************************************************************

    SDL_RenderPresent(sdl_renderer);
};

/**
 * Creates and Loads textures to be used for the End Menu
 */
void Renderer::LoadEndMenuResources(ResourceManager &resources)
{
    SDL_Color white = {255, 255, 255};
    TTF_Font *Sans = TTF_OpenFont("../Fonts/open-sans.ttf", 72);
    if (!Sans)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    resources.LoadText(sdl_renderer, "Game Over", Sans, white);
    resources.LoadText(sdl_renderer, ("Your Score: "), Sans, white);
};

/**
 * Creates and loads Textures related to the UI
 */
void Renderer::LoadUI(ResourceManager &resources)
{
    SDL_Color white = {255, 255, 255};
    TTF_Font *Sans = TTF_OpenFont("../Fonts/open-sans.ttf", 72);
    if (!Sans)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    resources.LoadText(sdl_renderer, ("Score: "), Sans, white);
    resources.LoadTexture(sdl_renderer, ("Health Bar Outline"), "../Resources/Images/health bar_outline.png");
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
    
    resources.LoadText(sdl_renderer, ("Wizard Demo"), Sans, white);
    resources.LoadText(sdl_renderer, ("Survive as long as you can"), Sans, white);
    resources.LoadText(sdl_renderer, ("Move with W, A, S, D"), Sans, white);
    resources.LoadText(sdl_renderer, ("Aim and shoot with mouse"), Sans, white);
    resources.LoadText(sdl_renderer, ("To continue, Press any key"), Sans, white);
    
};

/**
 * Renders everything related to the UI
 */
void Renderer::RenderUI(ResourceManager &resources, Character &character)
{
    //Render health bar
    SDL_Rect health_bar;
    health_bar.w = (252.0 / character.max_health) * character.health_; //252 is pixel size of outline of health_bar
    health_bar.h = health_bar_outline_.h - 4;
    health_bar.x = health_bar_outline_.x + 2;
    health_bar.y = health_bar_outline_.y + 2;

    SDL_Rect energy_bar;
    energy_bar.w = (252.0 / character.max_energy) * character.energy;
    energy_bar.h = energy_bar_outline_.h - 4;
    energy_bar.x = energy_bar_outline_.x + 2;
    energy_bar.y = energy_bar_outline_.y + 2;

    SDL_SetRenderDrawColor(sdl_renderer, 255, 15, 0, 255); //Set Color to red
    SDL_RenderFillRect(sdl_renderer, &health_bar);         //Draw health bar

    SDL_SetRenderDrawColor(sdl_renderer, 15, 50, 255, 255); //Set Color to blue
    SDL_RenderFillRect(sdl_renderer, &energy_bar);          //Draw energy bar

    //Render Health Bar Outline
    SDL_RenderCopy(sdl_renderer, resources.getTexture("Health Bar Outline"), NULL, &health_bar_outline_);
    //Render Energy Bar Outline
    SDL_RenderCopy(sdl_renderer, resources.getTexture("Health Bar Outline"), NULL, &energy_bar_outline_);
    //Render Score:
    SDL_RenderCopy(sdl_renderer, resources.getTexture("Score: "), NULL, &score_rect_);
    //Render physical score
    int score = character.score;
    int reversescore = 0;
    std::vector<int> scoredigits;
    while (score >= 10)
    {
        reversescore = score % 10;
        score = score / 10;
        scoredigits.push_back(reversescore);
    }
    scoredigits.push_back(score);
    int digits = 0;
    while (scoredigits.size() > 0)
    {
        score = scoredigits.back();
        digit_rect_.x = ((score_rect_.x + (score_rect_.w)) + (digits * digit_rect_.w));
        SDL_RenderCopy(sdl_renderer, resources.getTexture(std::to_string(score)), NULL, &digit_rect_);
        digits += 1;
        scoredigits.pop_back();
    }
};

/**
 * Sets up location of Menu Buttons on screen and puts
 * them into a vector to be used later
 */
void Renderer::LoadEndMenuBoxes(std::vector<MenuBoxes> &menuBoxes, ResourceManager &resources)
{
    SDL_Color white = {255, 255, 255};
    TTF_Font *Sans = TTF_OpenFont("../Fonts/open-sans.ttf", 72);
    if (!Sans)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }

    menuBoxes.clear();
    play_again_.x = 400;
    play_again_.y = 400;
    play_again_.w = 250;
    play_again_.h = 100;
    menuBoxes.emplace_back(MenuBoxes(play_again_, false));

    quit_.x = 400;
    quit_.y = 600;
    quit_.w = 250;
    quit_.h = 100;
    menuBoxes.emplace_back(MenuBoxes(quit_, false));
    
    resources.LoadText(sdl_renderer, "Play Again", Sans, white);
    resources.LoadText(sdl_renderer, "  Quit  ", Sans, white);
};

/**
 * Loads necessary components for the pause menu
 */
void Renderer::LoadPauseMenu(std::vector<MenuBoxes> &menuBoxes, ResourceManager &resources){
    float percent = 1024/100;
    SDL_Color white = {255, 255, 255};
    TTF_Font *Sans = TTF_OpenFont("../Fonts/open-sans.ttf", 36);
    if (!Sans)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    int w,h;

    pause_menu_boxes[0].w = 250; //Resume background box
    pause_menu_boxes[0].h = 100;
    pause_menu_boxes[0].x = (50*percent) - (pause_menu_boxes[0].w / 2);
    pause_menu_boxes[0].y = (50*percent) - (pause_menu_boxes[0].h / 2);

    TTF_SizeText(Sans, "Resume Game", &w, &h);
    pause_menu_boxes[1].w = w; //Resume text
    pause_menu_boxes[1].h = h;
    pause_menu_boxes[1].x = (50*percent) - (pause_menu_boxes[1].w / 2);
    pause_menu_boxes[1].y = (50*percent) - (pause_menu_boxes[1].h / 2);

    pause_menu_boxes[2].w = 250; //Quit background box
    pause_menu_boxes[2].h = 100;
    pause_menu_boxes[2].x = (50*percent) - (pause_menu_boxes[2].w / 2);
    pause_menu_boxes[2].y = (70*percent) - (pause_menu_boxes[2].h / 2);

    TTF_SizeText(Sans, "Quit", &w, &h);
    pause_menu_boxes[3].w = w; //Quit text
    pause_menu_boxes[3].h = h;
    pause_menu_boxes[3].x = (50*percent) - (pause_menu_boxes[3].w / 2);
    pause_menu_boxes[3].y = (70*percent) - (pause_menu_boxes[3].h / 2);

    menuBoxes.emplace_back(MenuBoxes(pause_menu_boxes[0], false));
    menuBoxes.emplace_back(MenuBoxes(pause_menu_boxes[1], false));
    menuBoxes.emplace_back(MenuBoxes(pause_menu_boxes[2], false));
    menuBoxes.emplace_back(MenuBoxes(pause_menu_boxes[3], false));

    resources.LoadText(sdl_renderer, "Resume Game", Sans, white);
    resources.LoadText(sdl_renderer, "Quit", Sans, white);
    
};

/**
 * Creates the introduction page to giving instructions
 * on how to play the game.
 */
void Renderer::StartPage(ResourceManager &resources, bool &allowControl) {
    TTF_Font *Sans = TTF_OpenFont("../Fonts/open-sans.ttf", 72);
    if (!Sans)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    float percent = 1024/100;
    int w,h;
    //Set the background color
    SDL_SetRenderDrawColor(sdl_renderer, 90, 90, 90, 255);
    SDL_RenderClear(sdl_renderer);
    SDL_Rect box[5];

    TTF_SizeText(Sans, "Wizard Demo", &w, &h);
    box[0].w = w;
    box[0].h = h;
    box[0].x = (50*percent) - (box[0].w / 2);
    box[0].y = (10*percent) - (box[0].h / 2);

    TTF_SizeText(Sans, "Survive as long as you can", &w, &h);
    box[1].w = w;
    box[1].h = h;
    box[1].x = (50*percent) - (box[1].w / 2);
    box[1].y = (25*percent) - (box[1].h / 2);

    TTF_SizeText(Sans, "Move with W, A, S, D", &w, &h);
    box[2].w = w;
    box[2].h = h;
    box[2].x = (50*percent) - (box[2].w / 2);
    box[2].y = (50*percent) - (box[2].h / 2);

    TTF_SizeText(Sans, "Aim and shoot with mouse", &w, &h);
    box[3].w = w;
    box[3].h = h;
    box[3].x = (50*percent) - (box[3].w / 2);
    box[3].y = (60*percent) - (box[3].h / 2);

    TTF_SizeText(Sans, "To continue, Press any key", &w, &h);
    box[4].w = w;
    box[4].h = h;
    box[4].x = (50*percent) - (box[4].w / 2);
    box[4].y = (85*percent) - (box[4].h / 2);

    SDL_RenderCopy(sdl_renderer, resources.getTexture("Wizard Demo"), NULL, &box[0]);
    SDL_RenderCopy(sdl_renderer, resources.getTexture("Survive as long as you can"), NULL, &box[1]);
    SDL_RenderCopy(sdl_renderer, resources.getTexture("Move with W, A, S, D"), NULL, &box[2]);
    SDL_RenderCopy(sdl_renderer, resources.getTexture("Aim and shoot with mouse"), NULL, &box[3]);
    if(allowControl){
        SDL_RenderCopy(sdl_renderer, resources.getTexture("To continue, Press any key"), NULL, &box[4]); 
    }

    SDL_RenderPresent(sdl_renderer);
};

/**
 * Renderers all components of the pause menu
 */
void Renderer::PauseMenu(std::vector<MenuBoxes> &menuBoxes, ResourceManager &resources){
    SDL_SetRenderDrawColor(sdl_renderer, 90, 90, 90, 255);
    SDL_RenderClear(sdl_renderer);

    SDL_SetRenderDrawColor(sdl_renderer, 15, 15, 255, 255);
    if (menuBoxes[0].collision_ == true)
    {
        SDL_RenderFillRect(sdl_renderer, &(menuBoxes[0].box_));
        SDL_RenderCopy(sdl_renderer, resources.getTexture("Resume Game"), NULL, &menuBoxes[1].box_);
    }
    else
    {
        SDL_RenderDrawRect(sdl_renderer, &(menuBoxes[0].box_));
        SDL_RenderCopy(sdl_renderer, resources.getTexture("Resume Game"), NULL, &menuBoxes[1].box_);
    }

    SDL_SetRenderDrawColor(sdl_renderer, 255, 15, 15, 255);
    if (menuBoxes[2].collision_ == true)
    {
        SDL_RenderFillRect(sdl_renderer, &(menuBoxes[2].box_));
        SDL_RenderCopy(sdl_renderer, resources.getTexture("Quit"), NULL, &menuBoxes[3].box_);
    }
    else
    {
        SDL_RenderDrawRect(sdl_renderer, &(menuBoxes[2].box_));
        SDL_RenderCopy(sdl_renderer, resources.getTexture("Quit"), NULL, &menuBoxes[3].box_);
    }
    SDL_RenderPresent(sdl_renderer);
};