#ifndef WINDOW_H_
#define WINDOW_H_

#include "SDL2/SDL.h"
#include <iostream>

class Window{
 public:
  Window() = default;
  ~Window() = default;

  void close(std::ostream& log =std::cout );
  void get_window_center(int& x, int& y);
  void get_window_size(int& w, int& h);
  void get_renderer_size(int &w, int &h);
  void init(std::ostream& log=std::cout);
  void present();
  void reset_rendering(std::ostream& log = std::cout);
  void set_render_draw_color(SDL_Color C);
  void render_copy(SDL_Texture* t, const SDL_Rect* src, const SDL_Rect* dst,std::ostream& log = std::cout);
  SDL_Texture* create_texture_from_surface(SDL_Surface* S);
 private:
  SDL_Window *m_window = nullptr;
  SDL_Renderer *m_renderer = nullptr;
  int const m_WIDTH = 1280;
  int const m_HEIGHT = 960;
  int const m_SCALE = 1;
};



#endif // WINDOW_H_
