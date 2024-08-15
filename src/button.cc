  #include <iostream>
  #include "../include/button.h"
  #include "SDL2/SDL.h"
  #include "SDL2/SDL_image.h"
  #include "../include/log.h"
  #include "../include/texture_manager.h"



Button::Button(const std::string& key, SDL_Rect rect,SDL_Renderer* r, std::function<void()> action) : 
action(action),m_texture_key(key), m_rect(rect){
  if(g_TEXTURE.haskey(m_texture_key)){
    SDL_RenderCopy(r,g_TEXTURE.get(key),NULL,&m_rect);
  }
}


bool Button::pressed(int mouse_x, int mouse_y){
  if(mouse_x< m_rect.x) return false;
  if(mouse_x> m_rect.x+m_rect.w) return false;
  if(mouse_y< m_rect.y) return false;
  if(mouse_y> m_rect.y+ m_rect.h) return false;
  return true;
}
