#pragma once
#include <unordered_map>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "region.hpp"
#include "string"
#include "fstream"
#include "globals.hpp"
#include "country.hpp"
#include "unit.hpp"
#include "button.hpp"
#include "resources_manager.hpp"
#include "window.hpp"
#include <memory>

class Game
{
public:
  Game();
  ~Game();
  void start(Game_map&);
  void close_game();
  void render_table();
  Region* get_region(ID id){return &m_table.at(id);}
  void set_font(TTF_Font* f){m_font =f;}
  void get_input();
  void set_pointers(std::shared_ptr<Window>& w, std::shared_ptr<Resources_Manager> &r);

private:
  void read_map(const std::filesystem::path& filename);
  ID get_region_ID(const std::string & abb);
  std::unordered_map<ID,Region> m_table;
  std::unordered_map<ID,Country> m_countries;
  std::unordered_map<ID,Unit> m_units;
  std::string m_gamename;
  int m_board_w{}, m_board_h{}; // size in pixel of the board image.
  std::shared_ptr<Window> m_window = nullptr;
  std::shared_ptr<Resources_Manager> m_resources = nullptr;
  TTF_Font *m_font = nullptr;
  SDL_Event m_event;
  std::vector<Button> m_buttons;
  Button m_exit_button;
  bool m_running = false;
};
