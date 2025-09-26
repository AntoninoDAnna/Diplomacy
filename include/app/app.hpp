#pragma once
#include <fstream>
#include <vector>
#include <memory>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "core.hpp"
#include "app_scene.hpp"
#include "game.hpp"
#include "devel_tool.hpp"



class App{
public: 
  App() = default;
  ~App() = default;
  void show_scene();
  void init();
  void close();
  void open();

private:
  void handle_event();
  void get_event();
  void main_menu();
  void reset();
  void render_main_menu();
  void new_game();
  void render_new_game();
  void start_game(Game_map game);


private:
  std::shared_ptr<Core::Window> m_window = std::make_shared<Core::Window>();
  SDL_Event m_event;
  TTF_Font *m_font = nullptr;
  std::vector<Scene_id> m_scenes_stack{Scene_id::NONE};
  Scene_id m_next_scene = Scene_id::MAIN_MENU;
  Scene_id m_current_scene = Scene_id::NONE;
  Game m_game = Game();
  std::vector<Core::Button> m_buttons{};
  Core::Button m_exit_button;
  std::shared_ptr<Core::Manager> m_resources = std::make_shared<Core::Manager>();
  bool m_running = false;
  Devel_tool dt;
  bool dt_open = false;
};
