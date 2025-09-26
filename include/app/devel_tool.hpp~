#pragma once
#include "SDL_stdinc.h"
#include "window.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <memory>
#include <string>
#include "color.hpp"
#include "game.hpp"
#include "region.hpp"
class Devel_tool{
public:
  Devel_tool()  = default;
  ~Devel_tool();
  void init();
  void show();
  void close();
  void set_window(std::shared_ptr<Window>);
  void set_game(Game* game);
  // private methods

private:
  void init_imgui();
  void region_edit();
  void region_info(Region &region);
  void write_notes();
private:
  std::shared_ptr<Window> m_window;
  Game *m_game;
};
