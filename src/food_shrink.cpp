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

    // Here, basically we return immediately when the normal food is not being generated just now or when all type of special foods are generated.
    if(next_cycle <= 0) return false;
    
    // We are opening the possibility to generate this type food, so reduce the number of next cycle of food. 
    // If the last special food is generated, then next_cycle will be 0 which will then prevent the other type of special foods from being generated or even evaluated.
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
