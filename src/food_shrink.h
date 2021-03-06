#ifndef FOOD_SHRINK_H
#define FOOD_SHRINK_H

#define RANDOM_SIZE_MAX 100
#define SIZE_MIN 30

#include "food.h"
#include "snake.h"

class FoodShrink : public Food
{
public:
    FoodShrink(int grid_width, int grid_height, std::unique_ptr<Snake> &snake);
    bool EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) override;
    void RewardSnake(std::unique_ptr<Snake> &snake) override;
};

#endif