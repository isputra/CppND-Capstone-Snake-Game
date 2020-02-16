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
    ~Food();
    void RunThread(std::unique_ptr<Snake> &snake);
    void RunFoodCycle(std::unique_ptr<Snake> &snake);
    bool CheckIfFoodIsEaten(std::unique_ptr<Snake> &snake);
    void GenerateFood(std::unique_ptr<Snake> &snake);
    
    virtual bool EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake)=0;
    virtual void RewardSnake(std::unique_ptr<Snake> &snake)=0;

    SDL_Point getPosition() const { return _position; }
    int getID() { return _id; }

protected:
    SDL_Point _position;
    FoodType _type;
    int _id;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    std::vector<std::thread> threads;
    static std::mutex _mutex;
    static std::condition_variable _condition;

    bool start_game{true};
    bool is_eaten{false};
    bool is_active{true};
    static int next_cycle;

private:
    static int _idCnt;
};

#endif