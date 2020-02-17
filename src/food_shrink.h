#ifndef FOOD_SHRINK_H
#define FOOD_SHRINK_H

#include "food.h"
#include "snake.h"

class FoodShrink : public Food
{
public:
    FoodShrink(int grid_width, int grid_height, std::unique_ptr<Snake> &snake);
    ~FoodShrink(){std::cout << "FoodShrink::~FoodShrink() called..." << std::endl;}
    bool EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) override;
    void RewardSnake(std::unique_ptr<Snake> &snake) override;
};

#endif