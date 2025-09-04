#include "devel_tool.hpp"
#include "SDL_keyboard.h"
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


void Devel_tool::set_window(std::shared_ptr<Window> w) {
  LOGL("Shared window with Developer's tools");
  m_window = w;
}

Devel_tool::~Devel_tool() {
  close();
}

void Devel_tool::close() {
  if (m_window == nullptr)
    return;
  // if(m_window->is_open())
  //   m_window->close();
  m_window = nullptr;
}

void Devel_tool::init() {
  if (m_window == NULL) {
    LOGL("m_window is NULL. You have to share a window to Devel_tool");
    exit(EXIT_FAILURE);
  }
  init_imgui();
}

void Devel_tool::open_windget() {
  //std::cout << "Opening Windget" << std::endl;
  bool t = true;
  ImGui::Begin("Windget",&t,ImGuiWindowFlags_NoCollapse);
  ImGui::Text("Windget");
  ImGui::End();
}

void Devel_tool::show() {
  open_windget();
  return ;

  ImVec4 C = static_cast<ImVec4>(get_colour(colour));
  ImGuiIO *io =  &ImGui::GetIO();
  {
    static float f = 0.0f;
    static int counter = 0;

    if(show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("background color", (float*) &C); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
    ImGui::End();
  }
  if (show_another_window)
    {
      ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
        show_another_window = false;
      ImGui::End();
  }

  ImGui::Render();
  glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
  glClearColor(C.x * C.w, C.y * C.w, C.z *C.w,C.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  m_window->swap_window();
}

void Devel_tool::hide() {
  std::cout << "Minimized" << std::endl;
  m_window->minimize();
  if (!m_window->is_minimized())
    LOGL("Window is not minimized");
}

void Devel_tool::init_window() {
  m_window = std::make_shared<Window>();
  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  float main_scale = ImGui_ImplSDL2_GetContentScaleForDisplay(0);
  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_MINIMIZED);
  m_window->init("Developer's Tools", window_flags);
  m_window->set_scale(main_scale);
}

Uint32 Devel_tool::get_window_id() {
  if (m_window == nullptr)
    return 0;
  if (!m_window->is_open())
    return 0;
  return m_window->get_window_id();
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

void Devel_tool::handle_event(SDL_Event &event) {
  LOGL("Handleing events");
  const Uint8 *key_state;
  Window::Window_Message m;
  switch (event.type) {
  case SDL_WINDOWEVENT:
    m = m_window->handle_window_event(event);
    switch (m) {
    case Window::Window_Message::WINDOW_MINIMIZED:
      LOGL("Minimizing developer's tools");
      hide();
      break;
    case Window::Window_Message::WINDOW_MAXIMIZED:
      show();
      break;
    case Window::Window_Message::WINDOW_CLOSED:
      LOGL("Closing developer's tools");
      close();

      break;
    case Window::Window_Message::WINDOW_OPENED:
      LOGL("Opening developer's tools");
      if (!m_window->is_open())
        init();
      show();
      break;
    case Window::Window_Message::NONE:
      LOGL("None");
      break;
    }
    return;
  case SDL_KEYDOWN:
    key_state = SDL_GetKeyboardState(nullptr);
    if ((key_state[SDL_SCANCODE_LCTRL] || key_state[SDL_SCANCODE_RCTRL]) &&
        (key_state[SDL_SCANCODE_Q] || key_state[SDL_SCANCODE_D])) {
      LOGL("minimizing by keybord shortcut");
      m_window->minimize();
    }
    break;
  default:
    break;
  }

}
