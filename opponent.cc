#include "opponent.h"
#include <iostream>
#include <memory>
#include "cpputils/graphics/image.h"
#include "game_element.h"
using namespace std;

void Opponent::Draw(graphics::Image& opponent) {
  opponent.DrawRectangle(GetX(), GetY(), 50, 50, 246, 237, 13);
  opponent.DrawRectangle(GetX() + 11, GetY() + 6, 6, 7, 0, 0, 0);
  opponent.DrawRectangle(GetX() + 30, GetY() + 6, 6, 7, 0, 0, 0);
  opponent.DrawRectangle(GetX() + 3, GetY() + 28, 7, 4, 0, 0, 0);
  opponent.DrawRectangle(GetX() + 7, GetY() + 32, 11, 4, 0, 0, 0);
  opponent.DrawRectangle(GetX() + 15, GetY() + 36, 18, 4, 0, 0, 0);
  opponent.DrawRectangle(GetX() + 30, GetY() + 32, 11, 4, 0, 0, 0);
  opponent.DrawRectangle(GetX() + 38, GetY() + 28, 7, 4, 0, 0, 0);
}

void OpponentProjectile::Draw(graphics::Image& o_projectile) {
  o_projectile.DrawRectangle(GetX(), GetY(), 5, 5, 28, 240, 60);
}

void Opponent::Move(const graphics::Image& opponent) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(opponent)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
    graphics::Image opponent_;
    Draw(opponent_);
  }
}
std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  counter_ += 1;
  if (counter_ == 5) {
    std::unique_ptr<OpponentProjectile> projectile;
    projectile = std::make_unique<OpponentProjectile>();
    counter_ = 0;
    return projectile;
  } else {
    return nullptr;
  }
}

void OpponentProjectile::Move(const graphics::Image& o_projectile_) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(o_projectile_) == true) {
    SetIsActive(false);
  } else {
    graphics::Image o_projectile;
    Draw(o_projectile);
  }
}
