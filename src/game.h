#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food_normal.h"
#include "food_score.h"
#include "food_slow.h"
#include "food_shrink.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Init();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  void SetScore(int score);
  int GetSize() const;

 private:
  std::unique_ptr<Snake> snake;
  std::unique_ptr<FoodNormal> food_normal;
  std::unique_ptr<FoodScore> food_score;
  std::unique_ptr<FoodSlow> food_slow;
  std::unique_ptr<FoodShrink> food_shrink;
  
  std::mutex _mutex;

  int grid_width;
  int grid_height;

  void Update();
};

#endif