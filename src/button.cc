  #include <iostream>
  #include "../include/button.h"
  #include "SDL2/SDL.h"
  #include "SDL2/SDL_image.h"
  #include "../include/log.h"
  #include "../include/resources_manager.h"



template <class ReturnType>
_Button<ReturnType>::_Button(const std::string& key, SDL_Rect& rect,SDL_Renderer* r, std::function<ReturnType()> action,Resources_Manager& rm) : 
action(action),m_texture_key(key), m_rect(rect){
  SDL_RenderCopy(r,rm.get_texture(key),NULL,&m_rect);
}

template <class ReturnType>
_Button<ReturnType>::_Button(const std::string& key, SDL_Rect& rect,SDL_Renderer* r, std::function<ReturnType()> action,Resources_Manager* rm) : 
action(action),m_texture_key(key), m_rect(rect){
  SDL_RenderCopy(r,rm->get_texture(key),NULL,&m_rect);
}

template <class ReturnType>
_Button<ReturnType>::_Button(const _Button<ReturnType>& B) :
action(B.action),m_texture_key(B.m_texture_key),m_rect(B.m_rect){}

template <class ReturnType>
void _Button<ReturnType>::operator=(const _Button<ReturnType>& B){
  this->m_texture_key = B.m_texture_key;
  this->m_rect = B.m_rect;
  this->action = B.action;
}


template <class ReturnType>
bool _Button<ReturnType>::pressed(int mouse_x, int mouse_y){
  if(mouse_x< m_rect.x) return false;
  if(mouse_x> m_rect.x+m_rect.w) return false;
  if(mouse_y< m_rect.y) return false;
  if(mouse_y> m_rect.y+ m_rect.h) return false;
  return true;
}

template class _Button<void>;