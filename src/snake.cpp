#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    // std::cout<<"Update prev_cell.x = "<< std::to_string(prev_cell.x)<<" prev_cell.y = "<<std::to_string(prev_cell.y)<<std::endl;
    // std::cout<<"Update current_cell.x = "<< std::to_string(current_cell.x)<<" current_cell.y = "<<std::to_string(current_cell.y)<<std::endl;
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
  // std::cout<<"UpdateHead head_x = "<< std::to_string(head_x)<<" head_y = "<<std::to_string(head_y)<<std::endl;
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
  // std::cout<<"Body x = "<< std::to_string(item.x)<<" y = "<<std::to_string(item.y)<<std::endl;
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

void Snake::ShrinkBody(int number_body) {
  for(int i=0; i<number_body;i++) {
    body.erase(body.begin());
    size--;
  }
}

// Inefficient method to check if cell is occupied by snake->
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}
int Snake::GetScore() const { return _score; }
void Snake::SetScore(int score) { _score = score; }