#ifndef FOOD_SCORE_H
#define FOOD_SCORE_H

#define RANDOM_SCORE_MAX 100
#define SCORE_MIN 20

#include "food.h"
#include "snake.h"

class FoodScore : public Food 
{
public:
    FoodScore(int grid_width, int grid_height, std::unique_ptr<Snake> &snake);
    bool EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) override;
    void RewardSnake(std::unique_ptr<Snake> &snake) override;
};

#endif