#pragma once
#include <vector>
#include <memory>   
#include "button.h" 
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "texture_manager.h"
#include "game.h"
#include "globals.h"

class App{
public: 
  App();
  ~App();
  void show(Scene_id scene_id);
private:
  void get_window_center(int& x, int& y);
  void get_input();
  void reset_rendering();
  void main_menu();
  void render_main_menu();
  void new_game();
  void render_new_game();
  void start_game(Game_map game);
  void render_game();
private:
  int const m_WIDTH = 1280;
  int const m_HEIGHT = 960;
  int const m_SCALE = 1;
  SDL_Event m_event;
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  TTF_Font *m_font;
  std::vector<Scene_id> m_scenes{Scene_id::NONE};
  Game m_game = Game();
  std::vector<Button> m_buttons;
  Button m_exit_button;
};