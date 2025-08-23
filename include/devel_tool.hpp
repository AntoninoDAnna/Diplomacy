#pragma once
#include "SDL_stdinc.h"
#include "window.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <memory>
#include <string>

class Devel_tool{
public:
  Devel_tool()  = default;
  ~Devel_tool();
  void init();
  void init_window();
  void init_imgui();
  void show();
  void hide();
  void close();
  void handle_event(SDL_Event&);
  Uint32 get_window_id () const {return m_window->get_window_id();};

private:
  bool do_display = false;
  std::string m_glsl_version;
  std::shared_ptr<Window> m_window;
  ImGuiStyle* style;
  ImGuiIO *io;

  // temporary privite attribute to make it work in the demo thingy
private:
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
