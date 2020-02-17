#include "food_slow.h"

FoodSlow::FoodSlow(int grid_width, int grid_height, std::unique_ptr<Snake> &snake) :
    Food(grid_width, grid_height)
{
    std::unique_lock<std::mutex> lck(_mutex_cout);
    std::cout << "FoodSlow::FoodSlow..." << std::endl;
    lck.unlock();
    _type = FoodType::food_slow;
}

bool FoodSlow::EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) {
    std::unique_lock<std::mutex> lck(_mutex);
    if(next_cycle <= 0) return false;
    next_cycle = next_cycle - 1;
    lck.unlock();

    std::uniform_int_distribution<> distr(0, RANDOM_SPEED_MAX);
    float speed = snake->speed;
    float random = (distr(engine)/100.0);
    float speed_min = SPEED_MIN;
    return CheckSnakeCondition(speed, speed_min, random);
}


void FoodSlow::RewardSnake(std::unique_ptr<Snake> &snake) {
    snake->speed -= 0.01;
    std::unique_lock<std::mutex> lck(_mutex_cout);
    std::cout << "FoodSlow::RewardSnake speed="<< std::to_string(snake->speed) << std::endl;
    lck.unlock();
}
