#include <iostream>
#include "cpputils/graphics/image.h"
#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H
using namespace std;

class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}
  int GetX();
  int GetY();
  void SetX(int x_);
  void SetY(int y_);
  int GetWidth();
  int GetHeight();
  virtual void Draw(graphics::Image& element) = 0;
  bool GetIsActive();
  void SetIsActive(bool is_active);
  virtual void Move(const graphics::Image& element) = 0;
  bool IntersectsWith(GameElement* element);
  bool IsOutOfBounds(const graphics::Image& image);

 private:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active_ = true;
};

#endif
