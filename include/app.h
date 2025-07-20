#pragma once
#include <fstream>
#include <vector>
#include <memory>   
#include "button.h" 
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "resources_manager.h"
#include "game.h"
#include "globals.h"
#include "window.h"

enum class Scene_id{NONE, MAIN_MENU, NEW_GAME,GAME};

class App{
public: 
  App();
  ~App();
  void show(Scene_id scene_id);

private:
  void get_input();
  void main_menu();
  void reset();
  void render_main_menu();
  void new_game();
  void render_new_game();
  void start_game(Game_map game);
  void render_game();

private:
  std::shared_ptr<Window> m_window = std::make_shared<Window>();
  SDL_Event m_event;
  TTF_Font *m_font = nullptr;
  std::vector<Scene_id> m_scenes{Scene_id::NONE};
  Game m_game = Game();
  std::vector<Button> m_buttons{};
  Button m_exit_button;
  std::shared_ptr<Resources_Manager> m_resources = std::make_shared<Resources_Manager>();
  std::fstream m_log;
};
