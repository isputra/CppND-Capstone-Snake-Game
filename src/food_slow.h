#ifndef FOOD_SLOW_H
#define FOOD_SLOW_H

#define RANDOM_SPEED_MAX 90
#define SPEED_MIN 0.30f

#include "food.h"
#include "snake.h"

class FoodSlow : public Food 
{
public:
    FoodSlow(int grid_width, int grid_height, std::unique_ptr<Snake> &snake);
    bool EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) override;
    void RewardSnake(std::unique_ptr<Snake> &snake) override;
};

#endif