#pragma once

#include<unordered_map>
#include "region.h"
#include "diplomacy.h"
#include "string"
#include "fstream"
#include <filesystem>

typedef int ID;
class Game
{
public:
  Game(std::string game);
  ~Game();
  void start_game(std::string game);

private:
  void read_file(std::filesystem::path path);
  enum class units{NONE, FLEET, ARMY};
  std::unordered_map<ID,Region> table;
  std::fstream LOG;

};


