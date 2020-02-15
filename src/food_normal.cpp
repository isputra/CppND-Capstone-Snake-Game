#include "food_normal.h"

FoodNormal::FoodNormal(int grid_width, int grid_height, Snake &snake) :
    Food(grid_width, grid_height)
{
    std::cout << "FoodNormal::FoodNormal..." << std::endl;
    GenerateFood(snake);
}

bool FoodNormal::EvaluateIfFoodShouldBeGenerated(Snake &snake) {
    return is_eaten;
}

void FoodNormal::RewardSnake(Snake &snake) {
    std::cout << "FoodNormal::RewardSnake..." << std::endl;
    snake.SetScore(snake.GetScore()+1);
    snake.GrowBody();
    snake.speed += 0.02;
    std::cout << "snake.GetScore=" << snake.GetScore() << std::endl;
}
