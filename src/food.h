#ifndef FOOD_H
#define FOOD_H

#include <mutex>
#include <future>
#include <thread>
#include <vector>
#include <random>
#include "SDL.h"
#include "snake.h"

enum class FoodType { food_normal, food_score, food_slow, food_shrink };

class Food {
public:
    Food(int grid_width, int grid_height);
    ~Food();
    void RunThread(std::unique_ptr<Snake> &snake);
    void RunFoodCycle(std::unique_ptr<Snake> &snake);
    bool CheckIfFoodIsEaten(std::unique_ptr<Snake> &snake);
    void GenerateFood(std::unique_ptr<Snake> &snake);    
    void RemoveUntil();

    virtual bool EvaluateIfFoodShouldBeGenerated(std::unique_ptr<Snake> &snake)=0;
    virtual void RewardSnake(std::unique_ptr<Snake> &snake)=0;

    template <typename T>
    bool CheckSnakeCondition(T const &value_attribute, T const &value_min, T const &random_value) {
        if(value_attribute > value_min && random_value < value_attribute){
            if(first_food) {
                first_food = false;
                return true;
            }
            return is_eaten;
        }
        return false;
    }

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
    static std::mutex _mutex_cout;
    static std::mutex _mutex;
    static std::condition_variable _condition;

    bool first_food{true}; // Indicate if it's the first food generated.
    bool is_eaten{false}; // Detect whether the food is on the screen or not.
    bool is_active{true}; // Flag indicating we've stopped the game. Mainly used to prevent calling virtual method from parent class.
    static int next_cycle; // How many other type food that we want to generate.

private:
    static int _idCnt;
};

#endif