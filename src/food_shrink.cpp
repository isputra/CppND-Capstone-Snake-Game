#include "food_shrink.h"

FoodShrink::FoodShrink(int grid_width, int grid_height, std::unique_ptr<Snake> &snake) :
    Food(grid_width, grid_height)
{
    std::cout << "FoodShrink::FoodShrink..." << std::endl;
    _type = FoodType::food_shrink;
}

bool FoodShrink::EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) {
    std::unique_lock<std::mutex> lck(_mutex);
    if(next_cycle <= 0) return false;
    std::cout << "FoodShrink::EvaluateIfFoodShouldBeGenerated next_cycle=" << next_cycle << std::endl;
    next_cycle = next_cycle - 1;
    lck.unlock();

    std::uniform_int_distribution<int> distr(0, 100);
    int size = snake->size;
    int sizeMin = distr(engine);
    std::cout << "FoodShrink::EvaluateIfFoodShouldBeGenerated sizeMin="<< std::to_string(sizeMin) << " size="<< std::to_string(size) << std::endl;
    if(size > 1 && sizeMin < size){
        if(start_game) {
            std::cout << "FoodShrink::EvaluateIfFoodShouldBeGenerated start_game=" << start_game << std::endl;
            start_game = false;
            return true;
        }
        std::cout << "FoodShrink::EvaluateIfFoodShouldBeGenerated is_eaten=" << is_eaten << std::endl;
        return is_eaten;
    }
    return false;
}

void FoodShrink::RewardSnake(std::unique_ptr<Snake> &snake) {
    snake->ShrinkBody(1);
    std::cout << "FoodShrink::RewardSnake body="<< std::to_string((snake->body).size()) << std::endl;
    std::cout << "FoodShrink::RewardSnake size="<< std::to_string(snake->size) << std::endl;
}
