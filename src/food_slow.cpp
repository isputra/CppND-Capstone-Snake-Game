#include "food_slow.h"

FoodSlow::FoodSlow(int grid_width, int grid_height, std::unique_ptr<Snake> &snake) :
    Food(grid_width, grid_height)
{
    std::cout << "FoodSlow::FoodSlow..." << std::endl;
    _type = FoodType::food_slow;
}

bool FoodSlow::EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) {
    std::unique_lock<std::mutex> lck(_mutex);
    if(next_cycle <= 0) return false;
    std::cout << "FoodSlow::EvaluateIfFoodShouldBeGenerated next_cycle=" << next_cycle << std::endl;
    next_cycle = next_cycle - 1;
    lck.unlock();

    std::uniform_int_distribution<float> distr(0, 50);
    float speed = snake->speed;
    float random = distr(engine);
    float speedMin = random/100;
    std::cout << "FoodSlow::EvaluateIfFoodShouldBeGenerated speedMin="<< std::to_string(speedMin) << " speed="<< std::to_string(speed) << std::endl;
    if(speed > 0.1 && speedMin < speed){
        if(_position.x == -1 && _position.y == -1){
            // std::cout << "FoodSlow::EvaluateIfFoodShouldBeGenerated random="<< random << std::endl;
            return true;
        }
    }
    return false;
}

void FoodSlow::RewardSnake(std::unique_ptr<Snake> &snake) {
    snake->speed -= 0.01;
    std::cout << "FoodSlow::RewardSnake speed="<< std::to_string(snake->speed) << std::endl;
}
