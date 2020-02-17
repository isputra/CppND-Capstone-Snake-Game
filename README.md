# CPPND: Capstone Snake Game

This project is my version of Snake Game, which I developed as part of Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## Class Structure
There are several files/classes in this program : 
1. Game : Instantiate all the elements of the game such as Snake and Foods.
2. Controller : Handles the input from keyboard. It accepts key up, key down, key left, and key right which allow user to navigate the Snake.
3. Renderer : Renders all elements using SDL2.
4. Snake : Defines the behaviour of the snake such as its size, speed, and score.
5. Food : Base class of food element. Each food gives different reward after being eaten. There are 4 types of foods : 
  * Normal food (`FoodNormal`), which rewards the user normaly such as add score, grow the snake's body, and increase its speed. Every time the snake eat this type of food, another one will be generated immediately and placed randomly. Other type of food than this one may be called special food.
  * Score booster food (`FoodScore`), which gives more score that normal food, but it surfaces rarely and only when the Snake has achieved a high score.
  * Food that reduce speed (`FoodSlow`), which reduces the speed of the Snake. It appears rarely and only when the Snake runs too fast.
  * Food that shrink the body (`FoodShrink`), which trims the snake instead of growing it. It appears rarely and only when the Snake's body is too long.

Each food is spawn into its own thread which executes an infinite while loop that only stops when the Food class is destroyed (when the game is stopped). Inside each thread, we examine whether or not the food is eaten by the Snake, reward it accordingly, and decide whether or not to generate more foods or remove a food.

## Rubric Points
In this project, I've implemented at least these rubric points :
1. The project demonstrates an understanding of C++ functions and control structures: See Food.cpp line 37, 42, 44, 46, 55, 79.
2. The project uses Object Oriented Programming techniques: See Food.h line 15 to end.
3. Derived class functions override virtual base class functions. See food_score.h line 14, 15 and food_score.cpp line 12, 25.
4. The project uses smart pointers instead of raw pointers: See game.h line 26-30.
5. The project uses multithreading: See food.cpp line 27, 84.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.