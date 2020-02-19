#include "food_normal.h"

FoodNormal::FoodNormal(int grid_width, int grid_height, std::unique_ptr<Snake> &snake) :
    Food(grid_width, grid_height)
{
    std::unique_lock<std::mutex> lck(_mutex_cout);
    std::cout << "FoodNormal::FoodNormal..." << std::endl;
    lck.unlock();
    _type = FoodType::food_normal;
}

bool FoodNormal::EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) {
    if(first_food) {
        first_food = false;
        return true;
    }
    return is_eaten;
}

void FoodNormal::RewardSnake(std::unique_ptr<Snake> &snake) {
    snake->SetScore(snake->GetScore()+1);
    snake->GrowBody();
    snake->speed += 0.01;
    std::unique_lock<std::mutex> lck(_mutex_cout);
    std::cout << "FoodNormal::Rewardsnake score=" << snake->GetScore() <<" size="<< snake->size << " speed=" << snake->speed << std::endl;
    lck.unlock();
}

void FoodNormal::RemoveUntil() {} // normal food won't be removed in timely manner
