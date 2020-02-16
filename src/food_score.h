#ifndef FOOD_SCORE_H
#define FOOD_SCORE_H

#include "food.h"
#include "snake.h"

class FoodScore : public Food 
{
public:
    FoodScore(int grid_width, int grid_height, std::unique_ptr<Snake> &snake);
    ~FoodScore(){std::cout << "FoodScore::~FoodScore() called..." << std::endl;}
    bool EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) override;
    void RewardSnake(std::unique_ptr<Snake> &snake) override;
};

#endif