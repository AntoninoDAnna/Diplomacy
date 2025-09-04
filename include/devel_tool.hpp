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
  void hide();
  void close();
  void handle_event(SDL_Event&);
  Uint32 get_window_id();
  void set_window(std::shared_ptr<Window>);

  // private methods
private:
  void init_window();
  void init_imgui();
  void open_windget();


private:
  bool do_display = false;
  std::string m_glsl_version;
  std::shared_ptr<Window> m_window;

  // temporary privite attribute to make it work in the demo thingy
private:
  bool show_demo_window = true;
  bool show_another_window = false;
  Colours colour = Colours::BACKGROUND;
};
