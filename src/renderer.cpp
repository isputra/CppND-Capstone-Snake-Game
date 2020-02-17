#include "renderer.h"
#include <iostream>
#include <string>
#include <math.h>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(std::unique_ptr<Snake> &snake, 
                      std::unique_ptr<FoodNormal> &food_normal, 
                      std::unique_ptr<FoodScore> &food_score,
                      std::unique_ptr<FoodSlow> &food_slow,
                      std::unique_ptr<FoodShrink> &food_shrink
                      ) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  int pos_x;
  int pos_y;
  int diameter = (screen_width / grid_width + screen_height / grid_height)/2;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food normal
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0x00, 0xFF);
    block.x = food_normal->getPosition().x * block.w;
    block.y = food_normal->getPosition().y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

  // Render food score
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0xFF, 0xFF);
  pos_x = food_score->getPosition().x * diameter + diameter/2;
  pos_y = food_score->getPosition().y * diameter + diameter/2;
  DrawFilledCirle(sdl_renderer, pos_x, pos_y, diameter/2);

  // Render food slow
  SDL_SetRenderDrawColor(sdl_renderer, 0x7F, 0x7F, 0x7F, 0xFF);
  pos_x = food_slow->getPosition().x * diameter + diameter/2;
  pos_y = food_slow->getPosition().y * diameter + diameter/2;
  DrawFilledCirle(sdl_renderer, pos_x, pos_y, diameter/2);

  // Render food shrink
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0xFF, 0xFF);
  pos_x = food_shrink->getPosition().x * diameter + diameter/2;
  pos_y = food_shrink->getPosition().y * diameter + diameter/2;
  DrawCircle(sdl_renderer, pos_x, pos_y, diameter/2);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xCC, 0x7F, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x55, 0x7F, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

// source https://stackoverflow.com/a/48291620
void Renderer::DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

// source : https://discourse.libsdl.org/t/code-for-filled-circle/5699/3
void Renderer::DrawFilledCirle(SDL_Renderer *sdl_renderer, int x, int y, int r)
{
  int y1, y2;
  SDL_Rect rect;
  for(y1 = -r, y2 = r; y1; ++y1, --y2)
  {
    int xr = (int)(sqrt(r*r - y1*y1) + 0.5);
    rect.x = x - xr;
    rect.y = y + y1;
    rect.w = 2 * xr;
    rect.h = 1;
    SDL_RenderFillRect(sdl_renderer, &rect);
    rect.y = y + y2;
    rect.h = 1;
    SDL_RenderFillRect(sdl_renderer, &rect);
  }
  rect.x = x - r;
  rect.y = y;
  rect.w = 2 * r;
  rect.h = 1;
  SDL_RenderFillRect(sdl_renderer, &rect);
}
