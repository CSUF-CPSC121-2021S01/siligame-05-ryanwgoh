#include "game_element.h"
#include <iostream>
#include "cpputils/graphics/image.h"
using namespace std;

int GameElement::GetX() { return x_; }
int GameElement::GetY() { return y_; }
void GameElement::SetX(int x) { x_ = x; }
void GameElement::SetY(int y) { y_ = y; }
int GameElement::GetWidth() { return width_; }
int GameElement::GetHeight() { return height_; }

bool GameElement::GetIsActive() { return is_active_; }

void GameElement::SetIsActive(bool is_active) { is_active_ = is_active; }

bool GameElement::IntersectsWith(GameElement* element) {
  if (GetX() > element->GetX() + element->GetWidth() ||
      element->GetX() > GetX() + GetWidth() ||
      GetY() > element->GetY() + element->GetHeight() ||
      element->GetY() > GetY() + GetHeight()) {
    return false;
  } else {
    return true;
  }
}

bool GameElement::IsOutOfBounds(const graphics::Image& image) {
  if (GetY() + GetHeight() > image.GetHeight() ||
      GetX() + GetWidth() > image.GetWidth() || GetY() < 0 || GetX() < 0) {
    return true;
  } else {
    return false;
  }
}
