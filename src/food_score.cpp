#include "food_score.h"

FoodScore::FoodScore(int grid_width, int grid_height, std::unique_ptr<Snake> &snake) :
    Food(grid_width, grid_height)
{
    std::cout << "FoodScore::FoodScore..." << std::endl;
    _type = FoodType::food_score;
}

bool FoodScore::EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) {
    std::unique_lock<std::mutex> lck(_mutex);
    if(next_cycle <= 0) return false;
    std::cout << "FoodScore::EvaluateIfFoodShouldBeGenerated next_cycle=" << next_cycle << std::endl;
    next_cycle = next_cycle - 1;
    lck.unlock();

    std::uniform_int_distribution<int> distr(0, 30);
    int score = snake->GetScore();
    int score_min = distr(engine);
    std::cout << "FoodScore::EvaluateIfFoodShouldBeGenerated score_min="<< score_min << std::endl;
    if(score > 0 && score_min < score){
        if(start_game) {
            std::cout << "FoodScore::EvaluateIfFoodShouldBeGenerated start_game=" << start_game << std::endl;
            start_game = false;
            return true;
        }
        std::cout << "FoodScore::EvaluateIfFoodShouldBeGenerated is_eaten=" << is_eaten << std::endl;
        return is_eaten;
    }
    return false;
}

void FoodScore::RewardSnake(std::unique_ptr<Snake> &snake) {
    std::cout << "FoodScore::Rewardsnake->.." << std::endl;
    int score = snake->GetScore() / 10;
    snake->SetScore(snake->GetScore()+score);
    snake->GrowBody();
    std::cout << "snake->GetScore=" << snake->GetScore() << std::endl;
}
