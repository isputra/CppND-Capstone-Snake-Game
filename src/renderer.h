#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "snake.h"
#include "food_normal.h"
#include "food_score.h"
#include "food_slow.h"
#include "food_shrink.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(std::unique_ptr<Snake> &snake, 
              std::unique_ptr<FoodNormal> &food_normal, 
              std::unique_ptr<FoodScore> &food_score, 
              std::unique_ptr<FoodSlow> &food_slow,
              std::unique_ptr<FoodShrink> &food_shrink);
  void UpdateWindowTitle(int score, int fps);
  void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);
  void DrawFilledCirle(SDL_Renderer *screen, int x, int y, int r);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif