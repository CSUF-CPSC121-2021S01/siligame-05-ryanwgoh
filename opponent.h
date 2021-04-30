#include <iostream>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#ifndef OPPONENT_H
#define OPPONENT_H
#include <memory>
using namespace std;

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  void Draw(graphics::Image& o_projectile) override;
  void Move(const graphics::Image& o_projectile) override;
};

class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image& opponent) override;
  void Move(const graphics::Image& opponent) override;
  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int counter_ = 0;
};

#endif
