#include "food_normal.h"

FoodNormal::FoodNormal(int grid_width, int grid_height, std::shared_ptr<Snake> snake) :
    Food(grid_width, grid_height, snake)
{
    std::cout << "FoodNormal::FoodNormal..." << std::endl;
    GenerateFood();
}

bool FoodNormal::EvaluateIfFoodShouldBeGenerated() {
    return true;
}

void FoodNormal::RewardSnake() {
    std::cout << "FoodNormal::RewardSnake..." << std::endl;
    snake->SetScore(snake->GetScore()+1);
    snake->GrowBody();
    snake->speed += 0.02;
    std::cout << "snake->GetScore=" << snake->GetScore() << std::endl;
}
