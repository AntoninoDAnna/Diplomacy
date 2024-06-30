#pragma once

#include<unordered_map>
#include "region.h"
#include "diplomacy.h"

class Game
{
public:
  Game();
  ~Game();

private:
  enum class units{NONE, FLEET, ARMY};
  std::unordered_map<int,Region> table;
};

Game::Game()
{
}

Game::~Game()
{
}
