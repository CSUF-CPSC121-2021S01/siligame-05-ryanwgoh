#include "game.h"
#include <iostream>
#include <memory>
#include <vector>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

std::vector<std::unique_ptr<Opponent>>& Game::GetOpponents() {
  return opponent_;
}
std::vector<std::unique_ptr<OpponentProjectile>>&
Game::GetOpponentProjectiles() {
  return o_projectile_;
}
std::vector<std::unique_ptr<PlayerProjectile>>& Game::GetPlayerProjectiles() {
  return p_projectile_;
}
Player& Game::GetPlayer() { return player_; }
graphics::Image& Game::GetGameScreen() { return screen_; }

void Game::CreateOpponents() {
  std::unique_ptr<Opponent> opponent;
  srand((unsigned)time(0));
  for (int i = 0; i < 3; i++) {
    opponent = std::make_unique<Opponent>();
    int x = rand() % 750;
    int y = rand() % 550;
    opponent->SetX(x);
    opponent->SetY(y);
    opponent_.push_back(std::move(opponent));
  }
}

void Game::Init() {
  srand((unsigned)time(0));
  int x = rand() % 749;
  int y = rand() % 549;
  player_.SetX(x);
  player_.SetY(y);
  screen_.AddMouseEventListener(*this);
  screen_.AddAnimationEventListener(*this);
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponent_.size(); i++) {
    opponent_[i]->Move(screen_);
  }
  for (int j = 0; j < o_projectile_.size(); j++) {
    o_projectile_[j]->Move(screen_);
  }
  for (int k = 0; k < p_projectile_.size(); k++) {
    p_projectile_[k]->Move(screen_);
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (player_.IntersectsWith(opponent_[i].get()) == true) {
      player_.SetIsActive(false);
      opponent_[i]->SetIsActive(false);
      lost_ = true;
    }
  }
  for (int i = 0; i < p_projectile_.size(); i++) {
    for (int j = 0; j < opponent_.size(); j++) {
      if (p_projectile_[i]->IntersectsWith(opponent_[j].get()) == true) {
        p_projectile_[i]->SetIsActive(false);
        opponent_[j]->SetIsActive(false);
        if (player_.GetIsActive() == true) {
          score_ = score_ + 1;
        }
      }
    }
  }
  for (int i = 0; i < o_projectile_.size(); i++) {
    if (o_projectile_[i]->IntersectsWith(&player_) == true) {
      player_.SetIsActive(false);
      o_projectile_[i]->SetIsActive(false);
      lost_ = true;
    }
  }
}

void Game::UpdateScreen() {
  string score = std::to_string(GetScore());
  string text = "score: " + score;
  screen_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  screen_.DrawText(0, 0, text, 50, 245, 69, 66);
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive() == true) {
      opponent_[i]->Draw(screen_);
    }
  }
  for (int j = 0; j < o_projectile_.size(); j++) {
    if (o_projectile_[j]->GetIsActive() == true) {
      o_projectile_[j]->Draw(screen_);
    }
  }
  for (int k = 0; k < p_projectile_.size(); k++) {
    if (p_projectile_[k]->GetIsActive() == true) {
      p_projectile_[k]->Draw(screen_);
    }
  }
  if (player_.GetIsActive() == true) {
    player_.Draw(screen_);
  } else {
    screen_.DrawText(300, 300, "Game over", 100, 245, 69, 66);
  }
}

int Game::GetScore() { return score_; }

bool Game::HasLost() { return lost_; }

void Game::OnAnimationStep() {
  if (opponent_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  screen_.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent& mouse) {
  if (mouse.GetMouseAction() == graphics::MouseAction::kPressed ||
      mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> projectile;
    projectile = std::make_unique<PlayerProjectile>();
    projectile->SetX(mouse.GetX());
    projectile->SetY(mouse.GetY());
    p_projectile_.push_back(std::move(projectile));
  }
  if (mouse.GetX() < screen_.GetWidth() && mouse.GetY() < screen_.GetHeight() &&
      mouse.GetX() > 0 && mouse.GetY() > 0) {
    player_.SetX(mouse.GetX() - player_.GetWidth() / 2);
    player_.SetY(mouse.GetY() - player_.GetHeight() / 2);
  }
}

void Game::Start() { screen_.ShowUntilClosed(); }

void Game::RemoveInactive() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive() == false) {
      opponent_.erase(opponent_.begin() + i);
      i = i - 1;
    }
  }
  for (int i = 0; i < o_projectile_.size(); i++) {
    if (o_projectile_[i]->GetIsActive() == false) {
      o_projectile_.erase(o_projectile_.begin() + i);
      i = i - 1;
    }
  }
  for (int i = 0; i < p_projectile_.size(); i++) {
    if (p_projectile_[i]->GetIsActive() == false) {
      p_projectile_.erase(p_projectile_.begin() + i);
      i = i - 1;
    }
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> projectile;
      projectile = std::make_unique<OpponentProjectile>();
      projectile->SetX(opponent_[i]->GetX());
      projectile->SetY(opponent_[i]->GetY());
      o_projectile_.push_back(std::move(projectile));
    }
  }
}
