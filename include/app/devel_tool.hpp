#pragma once
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include <memory>
#include <string>
#include "game.hpp"
#include "region.hpp"
#include "core.hpp"

class Devel_tool{
public:
  Devel_tool()  = default;
  ~Devel_tool();
  void init();
  void show();
  void close();
  void share_ctx(Core::Context* ctx);
  void set_game(Game* game);
  // private methods

private:
  void init_imgui();
  void region_edit();
  void region_info(Region &region);
  void write_notes();
private:
  Core::Context* ctx = nullptr;
  *m_game = nullptr;
};
