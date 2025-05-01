#pragma once

#include <unordered_map>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "region.h"
#include "string"
#include "fstream"
#include "globals.h"
#include "country.h"
#include "unit.h"
#include "button.h"
#include "resources_manager.h"


class Game
{
public:
  Game();
  ~Game();
  void start_game(Game_map game);
  void close_game();
  void render_table();
  Region* get_region(ID id){return &m_table.at(id);} 
  void set_renderer(SDL_Renderer *r){m_r =r;}
  void set_font(TTF_Font* f){m_font =f;}
  void set_resources_manager(Resources_Manager* r){m_resources = r;}
  void set_window(SDL_Window *w){m_w = w;}
  void get_input();

private:
  void read_map(std::filesystem::path filename);
  std::unordered_map<ID,Region> m_table;
  std::unordered_map<ID,Country> m_countries;
  std::unordered_map<ID,Unit> m_units;
  std::string m_gamename;
  int board_w{}, board_h{};
  
  //Game does not own these pointers. App does;
  SDL_Renderer*  m_r = nullptr;
  SDL_Window* m_w = nullptr;
  Resources_Manager* m_resources = nullptr;
  TTF_Font *m_font = nullptr;
  std::fstream m_log;
  // 
  SDL_Event m_event;
  std::vector<Button> m_buttons;
  Button m_exit_button;
};


