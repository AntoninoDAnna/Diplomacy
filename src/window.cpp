#include "window.hpp"
#include <SDL_opengl.h>
#include "log.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"


void Window::init(const char* title,SDL_WindowFlags wf)
{
  m_wf = wf;
//  m_title = title;
  m_window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,m_WIDTH*m_SCALE,m_HEIGHT*m_SCALE,m_wf);
  if(m_window==NULL){
    std::cerr << "Error in creating window, aborting" << std::endl;
    LOGL(SDL_GetError());
    exit(EXIT_FAILURE);
  }
  m_renderer =SDL_CreateRenderer(m_window,1,0);
  if(m_renderer==NULL){
    std::cerr << "Error in creating renderer, aborting" << std::endl;
    LOGL(SDL_GetError())
    exit(EXIT_FAILURE);
  }
  SDL_RenderSetScale(m_renderer,m_SCALE,m_SCALE);

  if(wf & SDL_WINDOW_OPENGL){
    m_gl_context = SDL_GL_CreateContext(m_window);
    if (m_gl_context == NULL){
      std::cerr << "Error in creating OpenGL context, aborting " << std::endl;
      LOGL(SDL_GetError());
      exit(EXIT_FAILURE);
    }
    std::cout << "window::Init making context current"<<std::endl;
  }else{
    LOGL("No OpenGL context requested")
  }
}


void Window::close(){
  LOGL("[Window: close()]  calling SDL_DestroyWindow()");
  SDL_DestroyWindow(m_window);
  m_window=nullptr;

  LOGL("[Window: close()] calling SDL_DestroyRenderer()");
  SDL_DestroyRenderer(m_renderer);
  m_renderer = nullptr;

  LOGL("[Window: close()] calling SDL_GL_DeleteContext()");
  SDL_GL_DeleteContext(m_gl_context);
  m_gl_context = nullptr;
}
void Window::get_window_center(int& x, int &y){
  int w,h;
  SDL_GetWindowSize(m_window,&w,&h);
  x = w/(2*m_SCALE);
  y = h/(2*m_SCALE);
}

void Window::set_render_draw_color(SDL_Color c){
  SDL_SetRenderDrawColor(m_renderer,c.r,c.b,c.g,c.a);
  SDL_RenderClear(m_renderer);
}

void Window::present(){
  SDL_RenderPresent(m_renderer);
}

void Window::reset_rendering(){
  if(SDL_RenderClear(m_renderer)<0)
    LOGL(SDL_GetError());
}

void Window::get_window_size(int &w, int &h){
  SDL_GetWindowSize(m_window,&w,&h);
}

void Window::get_renderer_size(int& w, int& h){
  SDL_GetRendererOutputSize(m_renderer,&w,&h);
}


void Window::render_copy(SDL_Texture* t, const SDL_Rect* src, const SDL_Rect* dst){
  if(SDL_RenderCopy(m_renderer,t,src,dst)!=0)
    LOGL(SDL_GetError());

}

SDL_Texture* Window::create_texture_from_surface(SDL_Surface *s){
  return SDL_CreateTextureFromSurface(m_renderer,s);
}

void Window::set_scale(int scale){
  if(m_window != NULL){
    std::cerr << "ERROR: Cannot set scale if window is already open" << std::endl;
    exit(EXIT_FAILURE);
  }
  m_SCALE = scale;
}

uint32_t Window::get_window_id(){
  return SDL_GetWindowID(m_window);
}

void Window::make_current(){
  SDL_GL_MakeCurrent(m_window, m_gl_context);
  SDL_GL_SetSwapInterval(1); // Enable vsync
}

#ifdef DEBUG
void Window::IMG_init_for_opengl(const char* glsl_v){
  ImGui_ImplSDL2_InitForOpenGL(m_window, m_gl_context);
  ImGui_ImplOpenGL3_Init(glsl_v);

}

void Window::swap_window(){
  SDL_GL_SwapWindow(m_window);
}
#endif
