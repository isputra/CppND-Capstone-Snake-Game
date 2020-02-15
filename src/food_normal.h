#ifndef FOOD_NORMAL_H
#define FOOD_NORMAL_H

#include "food.h"
#include "snake.h"

class FoodNormal : public Food 
{
public:
    FoodNormal(int grid_width, int grid_height, std::shared_ptr<Snake> snake);
    // ~FoodNormal(){std::cout << "FoodNormal::~FoodNormal() called..." << std::endl;}
    bool EvaluateIfFoodShouldBeGenerated() override;
    void RewardSnake() override;
};

#endif