#ifndef FOOD_NORMAL_H
#define FOOD_NORMAL_H

#include "food.h"
#include "snake.h"

class FoodNormal : public Food 
{
public:
    FoodNormal(int grid_width, int grid_height, Snake &snake);

    bool EvaluateIfFoodShouldBeGenerated(Snake &snake) override;
    void RewardSnake(Snake &snake) override;
};

#endif