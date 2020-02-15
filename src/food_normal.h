#ifndef FOOD_NORMAL_H
#define FOOD_NORMAL_H

#include "food.h"
#include "snake.h"

class FoodNormal : public Food 
{
public:
    FoodNormal(int grid_width, int grid_height, std::unique_ptr<Snake> &snake);
    ~FoodNormal(){std::cout << "FoodNormal::~FoodNormal() called..." << std::endl;}
    bool EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake);
    void RewardSnake(std::unique_ptr<Snake> &snake) override;
};

#endif