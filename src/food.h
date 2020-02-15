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
    Food(int grid_width, int grid_height, std::shared_ptr<Snake> snake);
    // ~Food(){std::cout << "Food::~Food() called..." << std::endl;}
    void RunThread();
    void RunFoodCycle();
    bool CheckIfFoodIsEaten();
    void GenerateFood();
    
    virtual bool EvaluateIfFoodShouldBeGenerated()=0;
    virtual void RewardSnake()=0;

    SDL_Point getPosition() const { return _position; }

    std::vector<std::thread> threads;
    std::shared_ptr<Snake> snake;

protected:
    SDL_Point _position;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

private:
};

#endif