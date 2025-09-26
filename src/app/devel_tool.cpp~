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
#include "game.hpp"

Devel_tool::~Devel_tool() {
  close();
}

void Devel_tool::init() {
  if (m_window == NULL) {
    LOGL("m_window is NULL. You have to share a window to Devel_tool");
    exit(EXIT_FAILURE);
  }
  if (m_game == NULL) {
    LOGL("m_game is NULL. You have to share a game to Devel_tool");
    exit(EXIT_FAILURE);
  }

  init_imgui();
}

void Devel_tool::region_info(Region &region) {
  static SDL_Rect *rect = NULL;
  static int step = 1;
  static int step_fast = 5;
  ImGui::Begin("Region Info", NULL);
  ImGui::Text("Name: %s\n", region.get_name().c_str());
  ImGui::Text("Abbr: %s\n", region.get_abbreviation().c_str());
  if (ImGui::CollapsingHeader("Box data")) {
    rect = &region.region_box;
    ImGui::InputScalar("x", ImGuiDataType_S32, &rect->x, &step,&step_fast);
    ImGui::InputScalar("y", ImGuiDataType_S32, &rect->y, &step,&step_fast);
    ImGui::InputScalar("w", ImGuiDataType_S32, &rect->w, &step,&step_fast);
    ImGui::InputScalar("h", ImGuiDataType_S32, &rect->h, &step,&step_fast);
  }
  ImGui::End();
}

void Devel_tool::region_edit() {
  static ID selected = 0; // Id can't be 0'
  ImGui::Begin("Region Edit", NULL);
  if (ImGui::CollapsingHeader("Regions list")) {
    for (auto &[id, R] : m_game->m_table) {
      if (ImGui::Selectable(R.get_name().c_str(), id == selected)) {
        if(selected == id) selected = 0;
        else selected = id;
      }
      if(selected ==id){
        R.set_render_flag();
        region_info(R);
      } else {
        R.unset_render_flag();
      }
    }
  }
  ImGui::End();
}

void Devel_tool::write_notes() {
  static char text[20000];
  ImGui::Begin("Notes",NULL);
  ImGui::InputTextMultiline("Notes",text,20000);
  ImGui::End();
}

void Devel_tool::show() {
  static bool regions_tool=false;
  ImGui::Begin("Developer's Tool",NULL);
  ImGui::Checkbox("Region's tools", &regions_tool);
  if (regions_tool) {
    region_edit();
  }
  write_notes();
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

void Devel_tool::set_game(Game *g) {
  m_game = g;
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

