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

    std::uniform_int_distribution<int> distr(0, 100);
    int score = snake->GetScore();
    int random = distr(engine);
    std::cout << "FoodScore::EvaluateIfFoodShouldBeGenerated random="<< random << std::endl;
    if(score > 10 && random < score){
        if(_position.x == -1 && _position.y == -1){
            // std::cout << "FoodScore::EvaluateIfFoodShouldBeGenerated random="<< random << std::endl;
            return true;
        }
    }
    return false;
}

void FoodScore::RewardSnake(std::unique_ptr<Snake> &snake) {
    std::cout << "FoodScore::Rewardsnake->.." << std::endl;
    int score = snake->GetScore() / 10;
    snake->SetScore(snake->GetScore()+score);
    snake->GrowBody();
    // snake->speed += 0.01;
    std::cout << "snake->GetScore=" << snake->GetScore() << std::endl;
}
