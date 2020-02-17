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

    std::uniform_int_distribution<> distr(0, 100);
    float speed = snake->speed;
    int random = distr(engine);
    float speedMin = random/100;
    std::cout << "FoodSlow::EvaluateIfFoodShouldBeGenerated speedMin="<< std::to_string(speedMin) << " speed="<< std::to_string(speed) << std::endl;
    if(speed > 0.1 && speedMin < speed){
        if(start_game) {
            std::cout << "FoodSlow::EvaluateIfFoodShouldBeGenerated start_game=" << start_game << std::endl;
            start_game = false;
            return true;
        }
        std::cout << "FoodSlow::EvaluateIfFoodShouldBeGenerated is_eaten=" << is_eaten << std::endl;
        return is_eaten;
    }
    return false;
}

void FoodSlow::RewardSnake(std::unique_ptr<Snake> &snake) {
    snake->speed -= 0.01;
    std::cout << "FoodSlow::RewardSnake speed="<< std::to_string(snake->speed) << std::endl;
}
