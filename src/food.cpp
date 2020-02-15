#include "food.h"
#include <future>

Food::Food(int grid_width, int grid_height, std::shared_ptr<Snake> snake) :
    engine(dev()),
    random_w(0, static_cast<int>(grid_width)),
    random_h(0, static_cast<int>(grid_height)),
    snake(snake)
{
    std::cout << "Food::Food..." << std::endl;
}

void Food::RunThread(){
    std::cout << "Food::RunThread..." << std::endl;
    threads.emplace_back(std::thread(&Food::RunFoodCycle, this));
}

void Food::RunFoodCycle(){
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if(EvaluateIfFoodShouldBeGenerated() == true)
        {
            if(CheckIfFoodIsEaten() == true)
            {
                GenerateFood();
                RewardSnake();
            }
        }
    }
}

bool Food::CheckIfFoodIsEaten(){
    int new_x = static_cast<int>(snake->head_x);
    int new_y = static_cast<int>(snake->head_y);
    // std::cout << "_position.x=" << _position.x << " new_x=" << new_x << std::endl;
    // std::cout << "_position.y=" << _position.y << " new_y=" << new_y << std::endl;
    if (_position.x == new_x && _position.y == new_y) {
        return true;
    }
    return false;
}

void Food::GenerateFood(){
    std::cout << "Generate Food..." << std::endl;
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        if (!snake->SnakeCell(x, y)) {
            _position.x = x;
            _position.y = y;
            return;
        }
    }
}
