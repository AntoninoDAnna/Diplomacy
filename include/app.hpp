#pragma once
#include <fstream>
#include <vector>
#include <memory>
#include "button.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "resources_manager.hpp"
#include "game.hpp"
#include "globals.hpp"
#include "window.hpp"
#include "devel_tool.hpp"

enum class Scene_id{NONE, MAIN_MENU, NEW_GAME,GAME};

inline std::ostream& operator<<(std::ostream& os, Scene_id s){
  switch(s){
  case Scene_id::NONE :
    os << "NONE";
    break;
  case Scene_id::MAIN_MENU :
    os << "MAIN MENU";
    break;
  case Scene_id::NEW_GAME :
    os << "NEW GAME";
    break;
  case Scene_id::GAME :
    os << "GAME";
    break;
  default:
    os << "NOT KNOWN";
    break;
  }
  return os;
}


class App{
public: 
  App() = default;
  ~App() = default;
  void show_scene();
  void init();
  void close();
  void open();
private:
  void get_input();
  void main_menu();
  void reset();
  void render_main_menu();
  void new_game();
  void render_new_game();
  void start_game(Game_map game);


private:
  std::shared_ptr<Window> m_window = std::make_shared<Window>();
  SDL_Event m_event;
  TTF_Font *m_font = nullptr;
  std::vector<Scene_id> m_scenes_stack{Scene_id::NONE};
  Scene_id m_next_scene = Scene_id::MAIN_MENU;
  Scene_id m_current_scene = Scene_id::NONE;
  Game m_game = Game();
  std::vector<Button> m_buttons{};
  Button m_exit_button;
  std::shared_ptr<Resources_Manager> m_resources = std::make_shared<Resources_Manager>();
  bool m_running = false;
  Devel_tool dt;
};
