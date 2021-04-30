#include "player.h"
#include <iostream>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"
using namespace std;

void Player::Draw(graphics::Image& player) {
  player.DrawRectangle(GetX(), GetY() + 13, 8, 7, 0, 0, 0);
  player.DrawRectangle(GetX() + 4, GetY() + 9, 31, 4, 0, 0, 0);
  player.DrawRectangle(GetX() + 4, GetY() + 20, 36, 4, 0, 0, 0);
  player.DrawRectangle(GetX() + 27, GetY() + 24, 3, 4, 0, 0, 0);
  player.DrawRectangle(GetX() + 30, GetY() + 28, 3, 3, 0, 0, 0);
  player.DrawRectangle(GetX() + 36, GetY() + 20, 4, 24, 0, 0, 0);
  player.DrawRectangle(GetX() + 40, GetY() + 41, 10, 3, 0, 0, 0);
  player.DrawRectangle(GetX() + 46, GetY() + 20, 4, 24, 0, 0, 0);
  player.DrawRectangle(GetX() + 39, GetY() + 17, 11, 3, 22, 142, 175);
  player.DrawRectangle(GetX() + 47, GetY() + 9, 3, 11, 22, 142, 175);
  player.DrawRectangle(GetX() + 35, GetY() + 9, 15, 3, 22, 142, 175);
  player.DrawRectangle(GetX() + 35, GetY() + 11, 4, 6, 22, 142, 175);
  player.DrawRectangle(GetX() + 43, GetY() + 6, 3, 3, 22, 142, 175);
  player.DrawRectangle(GetX() + 39, GetY() + 12, 8, 5, 18, 193, 240);
  player.DrawRectangle(GetX() + 8, GetY() + 13, 27, 7, 240, 185, 28);
  player.DrawRectangle(GetX() + 35, GetY() + 17, 4, 3, 240, 185, 28);
  player.DrawRectangle(GetX() + 40, GetY() + 20, 6, 21, 240, 185, 28);
}

void PlayerProjectile::Draw(graphics::Image& p_projectile) {
  p_projectile.DrawRectangle(GetX() + 2, GetY(), 1, 1, 0, 0, 0);
  p_projectile.DrawRectangle(GetX() + 1, GetY() + 1, 1, 4, 0, 0, 0);
  p_projectile.DrawRectangle(GetX() + 3, GetY() + 1, 1, 4, 0, 0, 0);
  p_projectile.DrawRectangle(GetX() + 2, GetY() + 4, 1, 1, 0, 0, 0);
  p_projectile.DrawRectangle(GetX() + 2, GetY() + 1, 1, 3, 132, 148, 147);
}

void Player::Move(const graphics::Image& player) {}

void PlayerProjectile::Move(const graphics::Image& p_projectile_) {
  SetY(GetY() - 3);
  if (IsOutOfBounds(p_projectile_) == true) {
    SetIsActive(false);
  } else {
    graphics::Image p_projectile;
    Draw(p_projectile);
  }
}
