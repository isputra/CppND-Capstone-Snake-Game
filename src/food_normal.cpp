#include "food_normal.h"

FoodNormal::FoodNormal(int grid_width, int grid_height, std::unique_ptr<Snake> &snake) :
    Food(grid_width, grid_height)
{
    std::cout << "FoodNormal::FoodNormal..." << std::endl;
    _type = FoodType::food_normal;
}

bool FoodNormal::EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) {
    if(first_food) {
        first_food = false;
        return true;
    }
    // std::cout << "FoodNormal::EvaluateIfFoodShouldBeGenerated.." << std::endl;
    return is_eaten;
}

void FoodNormal::RewardSnake(std::unique_ptr<Snake> &snake) {
    std::cout << "FoodNormal::Rewardsnake->.." << std::endl;
    snake->SetScore(snake->GetScore()+1);
    snake->GrowBody();
    snake->speed += 0.01;
    std::cout << "snake->GetScore=" << snake->GetScore() << std::endl;
}

void FoodNormal::RemoveUntil() {} // normal food won't be removed in timely manner
