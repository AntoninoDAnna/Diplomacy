#ifndef WINDOW_H_
#define WINDOW_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include <iostream>

class Window{
 public:
  Window() = default;
  ~Window() = default;
  void close(std::ostream& log =std::cout );
  void get_window_center(int& x, int& y);
  void get_window_size(int& w, int& h);
  void get_renderer_size(int &w, int &h);
  void init(SDL_WindowFlags wf = static_cast<SDL_WindowFlags>( SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE), std::ostream& log=std::cout);
  void present();
  void reset_rendering(std::ostream& log = std::cout);
  void set_render_draw_color(SDL_Color C);
  void render_copy(SDL_Texture* t, const SDL_Rect* src, const SDL_Rect* dst,std::ostream& log = std::cout);
  SDL_Texture* create_texture_from_surface(SDL_Surface* S);
  void set_scale(int scale);
  uint32_t get_window_id();
  SDL_WindowFlags get_window_flags(){return m_wf;};
 private:
  SDL_Window *m_window = NULL;
  SDL_Renderer *m_renderer = NULL;
  SDL_GLContext m_gl_context = NULL;
  SDL_WindowFlags m_wf;
  int m_WIDTH = 1280;
  int m_HEIGHT = 960;
  float m_SCALE = 1.0;

#ifdef DEBUG
  public:
  void IMG_init_for_opengl(std::string& glsl_v);
  void swap_window();
#endif
};



#endif // WINDOW_H_
