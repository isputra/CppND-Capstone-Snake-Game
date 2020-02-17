#include "food.h"
#include <future>

Food::Food(int grid_width, int grid_height) :
    engine(dev()),
    random_w(0, static_cast<int>(grid_width-1)),
    random_h(0, static_cast<int>(grid_height-1)),
    _position{-1,-1}
{
    _id = _idCnt++;
    std::unique_lock<std::mutex> lck(_mutex_cout);
    std::cout << "Food #" << getID() << " Constructor..."<< std::endl;
    lck.unlock();
}

Food::~Food(){
    is_active = false; // we need to signal the thread that the class has deen destroyed
    std::unique_lock<std::mutex> lck(_mutex_cout);
    std::cout << "Food #"<< getID() <<" destructor is called..." << std::endl;
    lck.unlock();
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}

void Food::RunThread(std::unique_ptr<Snake> &snake){
    threads.emplace_back(std::thread(&Food::RunFoodCycle, this, std::ref(snake)));
}

void Food::RunFoodCycle(std::unique_ptr<Snake> &snake){
    std::unique_lock<std::mutex> lck(_mutex_cout);
    std::cout << "Food #"<< getID() <<" RunFoodCycle with thread id=" << std::this_thread::get_id() << std::endl;
    lck.unlock();
    while (is_active)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if(CheckIfFoodIsEaten(snake) == true)
        {
            // Because of data race, we could call methods whose child class has been destructed.
            // Therefore here we need to check with is_active. 
            if(is_active) RewardSnake(snake);
        }
        if(is_active && EvaluateIfFoodShouldBeGenerated(snake) == true)
        {
            GenerateFood(snake);
        }
    }
}

bool Food::CheckIfFoodIsEaten(std::unique_ptr<Snake> &snake){
    int new_x = static_cast<int>(snake->head_x);
    int new_y = static_cast<int>(snake->head_y);

    if (_position.x == new_x && _position.y == new_y) {
        std::unique_lock<std::mutex> lck(_mutex_cout);
        std::cout << "Food #" << getID() << " is eaten at (" << _position.x << ", " << _position.y << ")" << std::endl;
        lck.unlock();
        _position.x=-1; // remove food from screen
        _position.y=-1;
        is_eaten = true;
        return true;
    }
    return false;
}

void Food::GenerateFood(std::unique_ptr<Snake> &snake){
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        if (!snake->SnakeCell(x, y)) {
            std::unique_lock<std::mutex> lck(_mutex_cout);
            std::cout << "Food #"<< getID() <<" is generated at x=" << x << " y=" << y << " thread id=" << std::this_thread::get_id() << std::endl;
            lck.unlock();
            _position.x = x;
            _position.y = y;
            is_eaten = false;
            if(_type == FoodType::food_normal) {
                std::lock_guard<std::mutex> lock(_mutex);
                next_cycle = _idCnt-1;
            } else {
                // set timer to remove food
                auto remove_thread = std::thread(&Food::RemoveUntil, this);
                remove_thread.detach();
            }
            return;
        }
    }
}

void Food::RemoveUntil(){
    std::unique_lock<std::mutex> lck(_mutex_cout);
    std::cout << "Food #" << getID() << " will be removed in 5 seconds.. thread id=" << std::this_thread::get_id() << std::endl;
    lck.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    if(is_eaten) return;

    _position.x=-1; // remove food from screen
    _position.y=-1;
    is_eaten = true;
}

int Food::_idCnt = 0;
int Food::next_cycle = 0;
std::mutex Food::_mutex;
std::mutex Food::_mutex_cout;
std::condition_variable Food::_condition;