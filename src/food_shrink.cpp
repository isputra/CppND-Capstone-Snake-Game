#include "food_shrink.h"

FoodShrink::FoodShrink(int grid_width, int grid_height, std::unique_ptr<Snake> &snake) :
    Food(grid_width, grid_height)
{
    std::unique_lock<std::mutex> lck(_mutex_cout);
    std::cout << "FoodShrink::FoodShrink..." << std::endl;
    lck.unlock();
    _type = FoodType::food_shrink;
}

bool FoodShrink::EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) {
    std::unique_lock<std::mutex> lck(_mutex);
    if(next_cycle <= 0) return false;
    next_cycle = next_cycle - 1;
    lck.unlock();

    std::uniform_int_distribution<int> distr(0, RANDOM_SIZE_MAX);
    int size = snake->size;
    int random = distr(engine);
    int size_min = SIZE_MIN;
    return CheckSnakeCondition(size, size_min, random);
}

void FoodShrink::RewardSnake(std::unique_ptr<Snake> &snake) {
    snake->ShrinkBody(1);
    std::unique_lock<std::mutex> lck(_mutex_cout);
    std::cout << "FoodShrink::RewardSnake size="<< std::to_string(snake->size) << std::endl;
    lck.unlock();
}
