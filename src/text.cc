#include "../include/text.h"
#include <string>

Text::Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  SDL_Renderer* r ){
    m_surf = TTF_RenderText_Solid(font,text.c_str(),color);
    m_texture = SDL_CreateTextureFromSurface(r,m_surf);
    SDL_RenderCopy(r,m_texture,NULL,&box);
  }

Text::~Text(){
  SDL_FreeSurface(m_surf);
  SDL_DestroyTexture(m_texture);
}