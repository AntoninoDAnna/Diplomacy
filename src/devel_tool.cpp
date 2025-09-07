#include "devel_tool.hpp"
#include "SDL_keyboard.h"
#include "SDL_messagebox.h"
#include "SDL_stdinc.h"
#include "SDL_video.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <cstdlib>
#include <memory>
#include "log.hpp"
#include "window.hpp"


Devel_tool::~Devel_tool() {
  close();
}

void Devel_tool::init() {
  if (m_window == NULL) {
    LOGL("m_window is NULL. You have to share a window to Devel_tool");
    exit(EXIT_FAILURE);
  }
  init_imgui();
}

void Devel_tool::show() {
  ImGui::Begin("  ",NULL);
  ImGui::Text("WORKING IN PROGRESS");
  ImGui::End();
}

void Devel_tool::close() {
  if (m_window == nullptr)
    return;
  // if(m_window->is_open())
  //   m_window->close();
  m_window = nullptr;
}

void Devel_tool::set_window(std::shared_ptr<Window> w) {
  LOGL("Shared window with Developer's tools");
  m_window = w;
}

void Devel_tool::init_imgui() {
  LOGL("Initializing imgui in developer's tools");
  float main_scale = 0.0;
  int w=0,h=0;
  m_window->get_window_size(&w, &h, &main_scale);
  m_window->make_current();
  ImGuiIO *io = &ImGui::GetIO();
  IMGUI_CHECKVERSION();

  (void)io;
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  ImGui::StyleColorsDark();

  ImGuiStyle* style = &ImGui::GetStyle();
  style->ScaleAllSizes(main_scale);
  style->FontScaleDpi = main_scale;
}

