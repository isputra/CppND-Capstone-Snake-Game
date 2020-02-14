#include "food.h"
#include <future>

Food::Food(int grid_width, int grid_height) :
    engine(dev()),
    random_w(0, static_cast<int>(grid_width)),
    random_h(0, static_cast<int>(grid_height))
{
    std::cout << "Food::Food..." << std::endl;
}

void Food::RunThread(Snake &snake){
    std::cout << "Food::RunThread..." << std::endl;
    threads.emplace_back(std::thread(&Food::RunFoodCycle, this, std::ref(snake)));
}

void Food::RunFoodCycle(Snake &snake){
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if(EvaluateIfFoodShouldBeGenerated(snake) == true)
        {
            if(CheckIfFoodIsEaten(snake) == true)
            {
                GenerateFood(snake);
                RewardSnake(snake);
            }
        }
    }
}

bool Food::CheckIfFoodIsEaten(Snake &snake){
    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);
    // std::cout << "_position.x=" << _position.x << " new_x=" << new_x << std::endl;
    // std::cout << "_position.y=" << _position.y << " new_y=" << new_y << std::endl;
    if (_position.x == new_x && _position.y == new_y) {
        return true;
    }
    return false;
}

void Food::GenerateFood(Snake &snake){
    std::cout << "Generate Food..." << std::endl;
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        if (!snake.SnakeCell(x, y)) {
            _position.x = x;
            _position.y = y;
            return;
        }
    }
}
