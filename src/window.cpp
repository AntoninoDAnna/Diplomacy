#include "window.hpp"
#include "log.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "SDL2/SDL.h"

SDL_Texture* Window::create_texture_from_surface(SDL_Surface *s){
  return SDL_CreateTextureFromSurface(m_renderer,s);
}

Window::~Window() {
  if (m_open)
    close();
  LOGL("window {} destroyed", m_title);
}

void Window::close() {
  if (!m_open)
    return;
  make_current();
//  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext(m_imgui_context);
  destroy_sdl_window();
  destroy_sdl_renderer();
  m_open = false;
  LOGL("window {} closed", m_title);
}

void Window::get_renderer_size(int &w, int &h) {
  if (SDL_GetRendererOutputSize(m_renderer, &w, &h) != 0) {
    LOGL("Error in getting renderer sizes for window {}: {}", m_title, SDL_GetError());
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
    restore();
    present();
    break;
  case SDL_WINDOWEVENT_SHOWN:
    restore();
    present();
    break;
  case SDL_WINDOWEVENT_HIDDEN:
    break;
  case SDL_WINDOWEVENT_MOVED:
    m_x = event.window.data1;
    m_y = event.window.data2;
    present();
    break;
  case SDL_WINDOWEVENT_SIZE_CHANGED:
    m_width = event.window.data1;
    m_height = event.window.data2;
    present();
    break;
  case SDL_WINDOWEVENT_MINIMIZED: /**< Window has been minimized */
    return Window_Message::WINDOW_MINIMIZED;
    break;
  case SDL_WINDOWEVENT_MAXIMIZED: /**< Window has been maximized */
    restore();
    present();
    return Window_Message::WINDOW_MAXIMIZED;
    break;
  case SDL_WINDOWEVENT_RESTORED:
    restore();
    present();
    break;
  case SDL_WINDOWEVENT_ENTER: /**< Window has gained mouse focus */
    break;
  case SDL_WINDOWEVENT_LEAVE: /**< Window has lost mouse focus */
    break;
  case SDL_WINDOWEVENT_FOCUS_GAINED: /**< Window has gained keyboard focus */
    break;
  case SDL_WINDOWEVENT_FOCUS_LOST: /**< Window has lost keyboard focus */
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
  case SDL_WINDOWEVENT_HIT_TEST: /**< Window had a hit test that wasn't
                                    SDL_HITTEST_NORMAL. */
    break;
  case SDL_WINDOWEVENT_ICCPROF_CHANGED: /**< The ICC profile of the window's
                                           display has changed. */
    break;
  case SDL_WINDOWEVENT_DISPLAY_CHANGED: /**< Window has been moved to display
                                           data1. */
    break;
  default:
    break;
  }
  return Window_Message::NONE;
}

void Window::imgui_init() {
  LOGL("Imgui initialization for window {}", m_title);
  m_imgui_context = ImGui::CreateContext();
  ImGui::SetCurrentContext(m_imgui_context);
  //ImGui_ImplSDL2_InitForOpenGL(m_window, m_gl_context);
  //ImGui_ImplOpenGL3_Init(m_glsl_version.c_str());
  ImGuiIO& io = ImGui::GetIO();
  IMGUI_CHECKVERSION();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
  ImGui::StyleColorsDark();
  ImGuiStyle& style = ImGui::GetStyle();
  style.ScaleAllSizes(m_scale);
  style.FontScaleDpi = m_scale;
  ImGui_ImplSDL2_InitForSDLRenderer(m_window,m_renderer);
  ImGui_ImplSDLRenderer2_Init(m_renderer);
}

void Window::imgui_new_frame() {
  make_current();
  ImGui_ImplSDL2_NewFrame();
  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui::NewFrame();
}

void Window::imgui_render() {
  ImGui::Render();
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),m_renderer);
}

void Window::init(const char* title,SDL_WindowFlags wf)
{
  LOGL("initializing window {}", title);
  m_title = std::string(title);
//  get_glsl_version();
  create_sdl_window(wf);
  m_window_id = SDL_GetWindowID(m_window);
  create_sdl_renderer();
  set_scale(m_scale);
  imgui_init();
  m_open=true;
}



bool Window::is_minimized() {
  return get_window_flags() & SDL_WINDOW_MINIMIZED;
}



bool Window::is_shown() { return get_window_flags() & SDL_WINDOW_SHOWN; }

bool Window::is_open() { return m_open; }


void Window::make_current(){
  SDL_GL_MakeCurrent(m_window, m_gl_context);
  SDL_GL_SetSwapInterval(1); // Enable vsync
  ImGui::SetCurrentContext(m_imgui_context);
}

Uint32 Window::get_window_flags() {
  return SDL_GetWindowFlags(m_window);

}
void Window::minimize() {
  LOGL("Hiding window {}", m_title);
  if (is_minimized())
    return;
  SDL_MinimizeWindow(m_window);
}

void Window::present() { SDL_RenderPresent(m_renderer); }

void Window::render_copy(SDL_Texture* t, const SDL_Rect* src, const SDL_Rect* dst){
  if(SDL_RenderCopy(m_renderer,t,src,dst)!=0)
    LOGL("Error while render_copy in window {}: {}", m_title,SDL_GetError());
}

void Window::reset_rendering(){
  if(SDL_RenderClear(m_renderer)<0)
    LOGL("Error while resetting window {}: {}", m_title,SDL_GetError());
}

void Window::restore() {
  SDL_RestoreWindow(m_window);
  present();
}

void Window::render_flush() {
  if (SDL_RenderFlush(m_renderer) != 0)
    LOGL("Error while renderering window {}: {}",m_title,SDL_GetError());
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
  if (!(get_window_flags() & SDL_WINDOW_OPENGL)){
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
   m_renderer  = SDL_CreateRenderer(m_window,1,SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
   if(m_renderer==NULL){
     LOGL("Error while creating renderer for window {}: {}",m_title,SDL_GetError());
     exit(EXIT_FAILURE);
   }
}

void Window::create_sdl_window(SDL_WindowFlags wf) {
  if (m_window != NULL) {
    SDL_DestroyWindow(m_window);
    LOGL("A window is already existing. Replaced");
  }
  m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, m_width * m_scale,
                              m_height * m_scale,
                              wf);
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
