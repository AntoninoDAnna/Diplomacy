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
  void handle_event(SDL_Event&);
  void set_window(std::shared_ptr<Core::Window> &w);
  void set_manager( std::shared_ptr<Core::Manager> &r);
  void set_buttons_vector(std::vector<Core::Button>* );
  void set_exit_button(Core::Button*);
  bool is_running() const{return m_running;};

  friend class Devel_tool;
private:
  void read_map(const std::filesystem::path& filename);
  ID get_region_ID(const std::string & abb);
  std::unordered_map<ID,Region> m_table;
  std::unordered_map<ID,Country> m_countries;
  std::unordered_map<ID,Unit> m_units;
  std::string m_gamename;
  int m_board_w{}, m_board_h{}; // size in pixel of the board image.
  std::shared_ptr<Core::Window> m_window = nullptr;
  std::shared_ptr<Core::Manager> m_resources = nullptr;
  TTF_Font *m_font = nullptr; //non owning
  std::vector<Core::Button>* m_buttons; //non owning
  Core::Button* m_exit_button; // non owining
  bool m_running = false;

};
