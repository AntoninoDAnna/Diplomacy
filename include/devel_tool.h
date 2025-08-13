#pragma once
#include "window.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <memory>
#include <string>

class Devel_tool{
public:
  Devel_tool()  = default;
  ~Devel_tool() = default;
  void init();
  void init_window();
  void init_imgui();
  void start();

private:
  bool do_display = false;
  std::string m_glsl_version;
  ImGuiStyle* style;
  ImGuiIO* io;
};
