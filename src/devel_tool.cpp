#include "devel_tool.hpp"
#include "SDL_keyboard.h"
#include "SDL_stdinc.h"
#include "SDL_video.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <memory>
#include "log.hpp"
#include "window.hpp"


Devel_tool::~Devel_tool() {
  close();
}

void Devel_tool::close() {
  if (m_window == nullptr)
    return;
  if(m_window->is_open())
    m_window->close();
  m_window = nullptr;
}

void Devel_tool::init(){
  init_window();
}

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font.
  //   You can also load multiple fonts and use ImGui::PushFont()/PopFont()
  //   to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you
  //   need to select the font among multiple.
  // - If the file cannot be loaded, the function will return a nullptr.
  //   Please handle those errors in your application (e.g. use an assertion,
  //   or display an error and quit).
  // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use
  //   Freetype for higher quality font rendering.
  // - Read 'docs/FONTS.md' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash
  //   \ in a string literal you need to write a double backslash \\ !
  // - Our Emscripten build process allows embedding fonts to be
  //   accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
  //style.FontSizeBase = 20.0f;
  //io.Fonts->AddFontDefault();
  //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf");
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf");
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf");
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf");
  //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf");
  //IM_ASSERT(font != nullptr);
  // Our state
void Devel_tool::show() {
  if (m_window == nullptr) {
    init();

  }
  if(m_window->is_minimized())
    m_window->restore();

  m_window->make_current();
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
  ImGui::ShowDemoWindow(&show_demo_window);

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
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

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
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  m_window->swap_window();
}

void Devel_tool::hide() {
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
  io = &ImGui::GetIO();
  IMGUI_CHECKVERSION();

  (void)io;
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  ImGui::StyleColorsDark();

  style = &ImGui::GetStyle();
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

//void Devel_tool::start(){
//  init_window();
//  init_imgui();
//  //
//  bool = show_demo_show_demo_window = false;
//  bool m_open = false;
//  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//  bool done = false;
//
//  while (!done)
//    {
//      // Poll and handle events (inputs, window resize, etc.)
//      // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//      // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
//      // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
//      // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//      SDL_Event event;
//      while (SDL_PollEvent(&event))
//        {
//          ImGui_ImplSDL2_ProcessEvent(&event);
//          if (event.type == SDL_QUIT)
//            done = true;
//          if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_window.get_window()))
//            done = true;
//        }
//      if (m_window.get_window_flags() & SDL_WINDOW_MINIMIZED)
//        {
//          SDL_Delay(10);
//          continue;
//        }
//
//      // Start the Dear ImGui frame
//
//      ImGui_ImplOpenGL3_NewFrame();
//      ImGui_ImplSDL2_NewFrame();
//      ImGui::NewFrame();
//
//      // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about
//      bool = show_demo_(show_demo_window){
//        ImGui::ShowDemoWindow(&show_demo_window);
//      }
//      // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
//      {
//        static float f = 0.0f;
//        static int counter = 0;
//
//        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//        ImGui::Checkbox("Another Window", &show_another_window);
//
//        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//
//        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//          counter++;
//        ImGui::SameLine();
//        ImGui::Text("counter = %d", counter);
//
//        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
//        ImGui::End();
//      }
//
//      // 3. Show another simple window.
//      if (show_another_window)
//        {
//          ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//          ImGui::Text("Hello from another window!");
//          if (ImGui::Button("Close Me"))
//            show_another_window = false;
//          ImGui::End();
//        }
//
//      // Rendering
//      ImGui::Render();
//      glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
//      glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//      glClear(GL_COLOR_BUFFER_BIT);
//      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//      m_window.swap_window();
//    }
//  // Cleanup
//  ImGui_ImplOpenGL3_Shutdown();
//  ImGui_ImplSDL2_Shutdown();
//  ImGui::DestroyContext();
//  m_window.close();
//  SDL_Quit();
//

//}
