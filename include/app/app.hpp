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

private:
  Core::Event m_event;
  Core::Context ctx{};
  App_State  m_state;
  std::unique_ptr<Core::Scene> scene = nullptr;
  Devel_tool dt;
  
};
