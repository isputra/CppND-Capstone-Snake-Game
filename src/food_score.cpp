#include "food_score.h"

FoodScore::FoodScore(int grid_width, int grid_height, std::unique_ptr<Snake> &snake) :
    Food(grid_width, grid_height)
{
    std::cout << "FoodScore::FoodScore..." << std::endl;
    _type = FoodType::food_score;
}

bool FoodScore::EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake) {
    // std::cout << "FoodScore::EvaluateIfFoodShouldBeGenerated.." << std::endl;
    // std::unique_lock<std::mutex> lck(_mutex);
    // _condition.wait(lck, [this]{ 
    //     std::cout << "FoodScore::EvaluateIfFoodShouldBeGenerated x=" << _position.x << " y=" << _position.y << " thread id=" << std::this_thread::get_id() << " next_cycle="<< next_cycle << std::endl;
    //     return next_cycle;
    //     });
    if(!next_cycle) return false;
    next_cycle = false;
    std::cout << "FoodScore::EvaluateIfFoodShouldBeGenerated passed next cycle.." << std::endl;

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
