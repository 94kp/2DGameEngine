#include "Game.h"
#include <iostream>
#include <SDL2/SDL.h>

Game::Game()
{
  isRunning = false;
  std::cout << "Constructor called" << std::endl; 
}

Game::~Game()
{
  std::cout << "Destructor called" << std::endl;
}

void Game::Initialise()
{
  // initialise window here
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "SDL initialisation failed" << std::endl;
    return;
  }

  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);

  windowWidth = 800; //displayMode.w;
  windowHeight = 600; //displayMode.h;
  
  window = SDL_CreateWindow(
      "myEngine", 
      SDL_WINDOWPOS_CENTERED, 
      SDL_WINDOWPOS_CENTERED, 
      windowWidth,
      windowHeight,
      SDL_WINDOW_BORDERLESS
      ); // raw pointer to a struct
      
  if (!window)
  {
    std::cerr << "Error creating SDL Window" << std::endl;
    return;
  }

  renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  
  if (!renderer)
  {
    std::cerr << "Error creating SDL renderer" << std::endl;
    return;
  }

  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  isRunning = true;
}

void Game::Run()
{
  while (isRunning)
  {
    ProcessInput();
    Update();
    Render();
  }
}

void Game::ProcessInput()
{
  SDL_Event sdlEvent;
  while(SDL_PollEvent(&sdlEvent))
  {
    switch(sdlEvent.type)
    {
      case SDL_QUIT:
        isRunning = false;
        break;
      case SDL_KEYDOWN:
        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
        {
          isRunning = false;
        }
        break;
    }
  };



}

void Game::Setup()
{

}

void Game::Update()
{

}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // Render game objects here

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect player = { 10, 10, 20, 20};
    SDL_RenderFillRect(renderer, &player);

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

