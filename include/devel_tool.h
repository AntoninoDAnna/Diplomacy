#pragma once
#include "app.h"
#include "window.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <memory>

class Devel_app{
public:
  Devel_app(App &app);
  ~Devel_app() = default;
  void init();
  void start();
  void init_window();
  void init_imgui();

private:
  App &m_app;
  Window m_window;
  std::string m_glsl_version;
  ImGuiIO m_io;
  ImGuiStyle m_style;
};
