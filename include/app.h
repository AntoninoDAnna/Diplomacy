#pragma once
#include <vector>
#include <memory>   
#include "button.h" 
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

enum class Scene_id{NONE, MAIN_MENU};

class App{
public: 
  App();
  ~App();
  void show(Scene_id scene_id);
private:
  int const m_WIDTH = 1280;
  int const m_HEIGHT = 960;
  int const m_SCALE = 1;
  SDL_Event m_event;
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
  TTF_Font *m_font;
  Scene_id m_current_scene{Scene_id::NONE};
  
  void render_main_menu();
};