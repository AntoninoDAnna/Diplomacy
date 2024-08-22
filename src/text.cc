#include "../include/text.h"
#include "../include/log.h"
#include "../include/texture_manager.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Text::Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  SDL_Renderer* r ):
text(text) {
  
  if(g_TEXTURE.haskey(text)){
    if(SDL_RenderCopy(r,g_TEXTURE.get(text),NULL,&box)!=0)
    LOG<<SDL_GetError()<<std::endl;
    return;
  }
  
  SDL_Surface* s = TTF_RenderText_Solid(font,text.c_str(),color);
  
  if(s==NULL)
    LOG<<SDL_GetError()<<std::endl;

  SDL_Texture* t = SDL_CreateTextureFromSurface(r,s);
  
  SDL_FreeSurface(s);

  if(!t)
    LOG<<SDL_GetError()<<std::endl;

  g_TEXTURE.add(text,t);  
  
  if(SDL_RenderCopy(r,t,NULL,&box)!=0)
    LOG<<SDL_GetError()<<std::endl;
}

