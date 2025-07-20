#include "../include/window.h"

void Window::init(std::ostream& log)
{
  // SDL_CreateWindowAndRenderer(WIDTH*SCALE,HEIGHT*SCALE,0,&window,&renderer);
  m_window = SDL_CreateWindow("Diplomacy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,m_WIDTH*m_SCALE,m_HEIGHT*m_SCALE,SDL_WINDOW_RESIZABLE);
  if(m_window==NULL){
    std::cerr << "Error in creating window, aborting" << std::endl;
    log << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  m_renderer =SDL_CreateRenderer(m_window,1,0);
  if(m_renderer==NULL){
    std::cerr << "Error in creating renderer, aborting" << std::endl;
    log << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  SDL_RenderSetScale(m_renderer,m_SCALE,m_SCALE);
}

void Window::close(std::ostream& log ){
  log << "[Window: close()]  calling SDL_DestroyWindow()" << std::endl;
  SDL_DestroyWindow(m_window);
  m_window=nullptr;

  log << "[Window: close()] calling SDL_DestroyRenderer()"<< std::endl;
  SDL_DestroyRenderer(m_renderer);
  m_renderer = nullptr;
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

void Window::reset_rendering(std::ostream& log){
  if(SDL_RenderClear(m_renderer)<0)
    log << SDL_GetError() << std::endl;
}

void Window::get_window_size(int &w, int &h){
  SDL_GetWindowSize(m_window,&w,&h);
}

void Window::get_renderer_size(int& w, int& h){
  SDL_GetRendererOutputSize(m_renderer,&w,&h);
}


void Window::render_copy(SDL_Texture* t, const SDL_Rect* src, const SDL_Rect* dst,std::ostream& log){
  if(SDL_RenderCopy(m_renderer,t,src,dst)!=0)
    log << SDL_GetError()<< std::endl;

}

SDL_Texture* Window::create_texture_from_surface(SDL_Surface *s){
  return SDL_CreateTextureFromSurface(m_renderer,s);
}
