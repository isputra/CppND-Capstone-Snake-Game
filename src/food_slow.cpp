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
    // std::cout << "FoodSlow::EvaluateIfFoodShouldBeGenerated next_cycle=" << next_cycle << std::endl;
    next_cycle = next_cycle - 1;
    lck.unlock();

    std::uniform_int_distribution<> distr(0, 10);
    float speed = snake->speed;
    float random = (distr(engine)/100.0);
    float speed_min = 0.10f;
    std::cout << "FoodSlow::EvaluateIfFoodShouldBeGenerated speed="<< std::to_string(speed) << " random="<< std::to_string(random) << " speed_min="<< std::to_string(speed_min) << std::endl;
    return CheckSnakeCondition(speed, speed_min, random);
    // if(speed > speed_min && random < speed){
    //     if(first_food) {
    //         std::cout << "FoodSlow::EvaluateIfFoodShouldBeGenerated first_food=" << first_food << std::endl;
    //         first_food = false;
    //         return true;
    //     }
    //     std::cout << "FoodSlow::EvaluateIfFoodShouldBeGenerated is_eaten=" << is_eaten << std::endl;
    //     return is_eaten;
    // }
    // return false;
}

void FoodSlow::RewardSnake(std::unique_ptr<Snake> &snake) {
    snake->speed -= 0.01;
    std::cout << "FoodSlow::RewardSnake speed="<< std::to_string(snake->speed) << std::endl;
}
