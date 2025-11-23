#pragma once
#include <unordered_map>
#include <filesystem>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <memory>
#include "region.hpp"
#include <string>
#include "globals.hpp"
#include "country.hpp"
#include "unit.hpp"
#include "core.hpp"
#include "app_scene.hpp"
#include <memory>

class Game : public Core::Scene
{
public:
  Game(Core::Context *ctx,App_State* as);
  ~Game();

  void on_event(Core::Event& e) override;
  void on_render() override;
  void on_update() override;

  friend class Devel_tool;
private:
  Region* get_region(ID id){return &m_table.at(id);}
  void close_game();
  void start();
  void read_map(const std::filesystem::path& filename);
  void render_table();
  ID get_region_ID(const std::string & abb);

  std::unordered_map<ID,Region> m_table;
  std::unordered_map<ID,Country> m_countries;
  std::unordered_map<ID,Unit> m_units;
  std::string m_gamename;
  int m_board_w{}, m_board_h{}; // size in pixel of the board image.
  std::vector<std::unique_ptr<Core::BButton<void>>> m_buttons;
  App_State* state;
};
