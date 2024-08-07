#include <iostream>
#include "../include/button.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

Button::Button(int x, int y, int w, int h, const  char* file, SDL_Renderer* r, void(*action)() ) :
action(action), m_rect(SDL_Rect{x,y,w,h}), m_surf(IMG_Load(file)), m_texture(SDL_CreateTextureFromSurface(r, m_surf)){
  SDL_RenderCopy(r, m_texture, NULL,&m_rect);
}

Button::Button(SDL_Rect& rect, const char* file, SDL_Renderer* r,void(*action)()) : 
action(action), m_rect(rect)
{
  m_surf = IMG_Load(file);
  m_texture = SDL_CreateTextureFromSurface(r,m_surf);
  SDL_RenderCopy(r,m_texture,NULL,&m_rect);
}

Button::~Button(){
  SDL_FreeSurface(m_surf);
  SDL_DestroyTexture(m_texture);
}

bool Button::pressed(int mouse_x, int mouse_y){
  if(mouse_x< m_rect.x) return false;
  if(mouse_x> m_rect.x+m_rect.w) return false;
  if(mouse_y< m_rect.y) return false;
  if(mouse_y> m_rect.y+ m_rect.h) return false;
  return true;
}
