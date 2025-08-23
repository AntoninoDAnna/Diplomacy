#include "window.hpp"
#include <SDL_opengl.h>
#include <cstdlib>
#include "SDL_video.h"
#include "log.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"


SDL_Texture* Window::create_texture_from_surface(SDL_Surface *s){
  return SDL_CreateTextureFromSurface(m_renderer,s);
}

void Window::close() {
  make_current();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  destroy_sdl_window();
  destroy_sdl_renderer();
  destroy_sdl_gl_context();
  m_open = false;
}

void Window::get_renderer_size(int &w, int &h) {
  if (SDL_GetRendererOutputSize(m_renderer, &w, &h) != 0) {
    LOGL("Error in getting renderer sizes for window {}", m_title);
  };
}

void Window::get_window_center(int& x, int &y){
  int w,h;
  get_window_size(&w,&h,NULL);
  x = w/(2*m_scale);
  y = h/(2*m_scale);
}

void Window::get_window_size(int *w, int *h, float *scale) {
  SDL_GetWindowSize(m_window, w, h);
  if (scale != NULL)
    *scale = m_scale;
}

Window::Window_Message Window::handle_window_event(SDL_Event &event) {
  switch (event.window.event) {
  case SDL_WINDOWEVENT_RESIZED:
    m_width = event.window.data1;
    m_height = event.window.data2;
    present();
    break;
  case SDL_WINDOWEVENT_EXPOSED:
    present();
    break;
  case SDL_WINDOWEVENT_SHOWN:
    m_shown = true;
    present();
    break;
  case SDL_WINDOWEVENT_HIDDEN:
    m_shown = false;
  case SDL_WINDOWEVENT_MOVED:
    m_x = event.window.data1;
    m_y = event.window.data2;
    present();
  case SDL_WINDOWEVENT_SIZE_CHANGED:
    m_width = event.window.data1;
    m_height = event.window.data2;
    present();
    break;
  case SDL_WINDOWEVENT_MINIMIZED: /**< Window has been minimized */
    m_minimized = true;
    return Window_Message::WINDOW_MINIMIZED;
    break;
  case SDL_WINDOWEVENT_MAXIMIZED: /**< Window has been maximized */
    m_minimized = false;
    present();
    return Window_Message::WINDOW_MAXIMIZED;
    break;
  case SDL_WINDOWEVENT_RESTORED:
    m_minimized = false;
    return Window_Message::WINDOW_OPENED;
    break;
  case SDL_WINDOWEVENT_ENTER: /**< Window has gained mouse focus */
    m_mouse_focus = true;
    break;
  case SDL_WINDOWEVENT_LEAVE: /**< Window has lost mouse focus */
    m_mouse_focus = false;
    break;
  case SDL_WINDOWEVENT_FOCUS_GAINED: /**< Window has gained keyboard focus */
    m_keybord_focus = true;
    break;
  case SDL_WINDOWEVENT_FOCUS_LOST: /**< Window has lost keyboard focus */
    m_keybord_focus = false;
    break;
  case SDL_WINDOWEVENT_CLOSE: /**< The window manager requests that the window
                                 be closed */
    close();
    return Window_Message::WINDOW_CLOSED;
    break;
  case SDL_WINDOWEVENT_TAKE_FOCUS: /**< Window is being offered a focus (should
                                      SetWindowInputFocus() on itself or a
                                      subwindow, or ignore) */
    break;
  case SDL_WINDOWEVENT_HIT_TEST:       /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
    break;
  case SDL_WINDOWEVENT_ICCPROF_CHANGED: /**< The ICC profile of the window's
                                           display has changed. */
    break;
  case SDL_WINDOWEVENT_DISPLAY_CHANGED: /**< Window has been moved to display data1. */
    break;
  default:
    break;
  }
  return Window_Message::NONE;
}

void Window::IMG_init_for_opengl() {
  LOGL("Initializing ImplSL for OpenGL");
  ImGui_ImplSDL2_InitForOpenGL(m_window, m_gl_context);
  LOGL("Initlializing implOpenGL3");
  ImGui_ImplOpenGL3_Init(m_glsl_version.c_str());
}

void Window::init(const char* title,SDL_WindowFlags wf)
{
  LOGL("initializing window {}", title);
  m_wf = wf;
  m_title = std::string(title);
  get_glsl_version();
  create_sdl_window();
  m_window_id = SDL_GetWindowID(m_window);
  create_sdl_renderer();
  set_scale(m_scale);
  m_imgui_context = ImGui::CreateContext();
  ImGui::SetCurrentContext(m_imgui_context);
  IMG_init_for_opengl();
  create_sdl_gl_context();
  m_minimized = false;
  m_full_screen = false;
  m_shown = true;
  m_open = true;
  m_mouse_focus = true;
  m_keybord_focus = true;

}

void Window::make_current(){
  SDL_GL_MakeCurrent(m_window, m_gl_context);
  SDL_GL_SetSwapInterval(1); // Enable vsync
  ImGui::SetCurrentContext(m_imgui_context);
}

void Window::minimize() {
  if (m_minimized)
    return;

  SDL_MinimizeWindow(m_window);
  m_minimized = true;
}

void Window::present() { SDL_RenderPresent(m_renderer); }

void Window::render_copy(SDL_Texture* t, const SDL_Rect* src, const SDL_Rect* dst){
  if(SDL_RenderCopy(m_renderer,t,src,dst)!=0)
    LOGL("y()] Error while render_copy in window {}: {}", m_title,SDL_GetError());
}

void Window::reset_rendering(){
  if(SDL_RenderClear(m_renderer)<0)
    LOGL("Error while resetting window {}: {}", m_title,SDL_GetError());
}

void Window::restore() {
  if(!m_minimized) return;
  SDL_RestoreWindow(m_window);
  m_minimized = false;
}

void Window::set_render_draw_color(SDL_Color c){
  SDL_SetRenderDrawColor(m_renderer,c.r,c.b,c.g,c.a);
  SDL_RenderClear(m_renderer);
}

void Window::set_scale(float scale){
  m_scale = scale <=0 ? 1.0 : scale;
  if(SDL_RenderSetScale(m_renderer,m_scale,m_scale) !=0)
    LOGL("Error in setting the scale in window {}: {}", m_title, SDL_GetError());
}

void Window::swap_window() { SDL_GL_SwapWindow(m_window); }


void Window::create_sdl_gl_context() {
  if (!(m_wf & SDL_WINDOW_OPENGL)){
    LOGL("No OpenGL context requested in window {}", m_title);
    return;
  }
  m_gl_context = SDL_GL_CreateContext(m_window);
  if (m_gl_context == NULL){
    LOGL("Error while creating OpenGL context in window {}: {}",m_title,SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void Window::create_sdl_renderer() {
   m_renderer  = SDL_CreateRenderer(m_window,1,0);
  if(m_renderer==NULL){
    LOGL("Error while creating renderer for window {}: {}",m_title,SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void Window::create_sdl_window() {
  if (m_window != NULL) {
    SDL_DestroyWindow(m_window);
    LOGL("A window is already existing. Replaced");
  }
  m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, m_width * m_scale,
                              m_height * m_scale,
                              m_wf);
  if(m_window==NULL){
    std::cerr << "Error in creating window, aborting" << std::endl;
    LOGL("Error while creating window {}: {}",m_title,SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void Window::get_glsl_version() {
    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100 (WebGL 1.0)
  m_glsl_version = "#version 100";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
  // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
  m_glsl_version = "#version 300 es";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
  // GL 3.2 Core + GLSL 150
  m_glsl_version = "#version 150";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
  // GL 3.0 + GLSL 130
  m_glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
  // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
  SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif
  LOGL("glsl version {}", m_glsl_version);
}

void Window::destroy_sdl_window() {
  LOGL("Destroying window {}", m_title);
  if (m_window == nullptr)
    return;
  SDL_DestroyWindow(m_window);
  m_window = nullptr;
}

void Window::destroy_sdl_renderer() {
  LOGL("Destroying renderer in window {}", m_title);
  if (m_renderer == nullptr)
    return;
  SDL_DestroyRenderer(m_renderer);
  m_renderer = nullptr;
}

void Window::destroy_sdl_gl_context() {
  LOGL("Destroying Gl context in window {}", m_title);
  if (m_gl_context == nullptr)
    return;
  SDL_GL_DeleteContext(m_gl_context);
  m_gl_context = nullptr;
}
