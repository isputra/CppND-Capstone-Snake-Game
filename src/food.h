#ifndef FOOD_H
#define FOOD_H

#include <mutex>
#include <future>
#include <thread>
#include <vector>
#include <random>
#include "SDL.h"
#include "snake.h"

enum class FoodType { food_normal, food_score, food_slow, food_stunt };

class Food {
public:
    Food(int grid_width, int grid_height);
    ~Food(){
        is_active = false;
        std::cout << "Food::~Food() called..." << std::endl;
        std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
            std::cout << "thread id=" << t.get_id() << std::endl;
            t.join();
        });
    }
    void RunThread(Snake &snake);
    void RunFoodCycle(Snake &snake);
    bool CheckIfFoodIsEaten(Snake &snake);
    void GenerateFood(Snake &snake);
    
    bool EvaluateIfFoodShouldBeGenerated(Snake &snake){
        // std::cout << "Food::EvaluateIfFoodShouldBeGenerated() called..." << std::endl;
        return false;
    }
    virtual void RewardSnake(Snake &snake)=0;

    SDL_Point getPosition() const { return _position; }

    std::vector<std::thread> threads;

protected:
    SDL_Point _position;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    bool is_eaten{false};
    bool is_active{true};

private:
};

#endif