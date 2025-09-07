#pragma once
#include "SDL_stdinc.h"
#include "window.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <memory>
#include <string>
#include "color.hpp"

class Devel_tool{
public:
  Devel_tool()  = default;
  ~Devel_tool();
  void init();
  void show();
  void close();
  void set_window(std::shared_ptr<Window>);

  // private methods
private:
  void init_imgui();


private:
  std::shared_ptr<Window> m_window;


};
