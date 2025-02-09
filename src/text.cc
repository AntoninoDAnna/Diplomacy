#include "../include/text.h"
#include "../include/log.h"
#include "../include/resources_manager.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Text::Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  SDL_Renderer* r, Resources_Manager* rm ):
text(text) {
  
  if(rm->haskey_texture(text)){
    if(SDL_RenderCopy(r,rm->get_texture(text),NULL,&box)!=0)
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

  rm->add_texture(text,t);  
  
  if(SDL_RenderCopy(r,t,NULL,&box)!=0)
    LOG<<SDL_GetError()<<std::endl;
}

Text::Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  SDL_Renderer* r, Resources_Manager& rm ):
text(text) {
  
  if(rm.haskey_texture(text)){
    if(SDL_RenderCopy(r,rm.get_texture(text),NULL,&box)!=0)
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

  rm.add_texture(text,t);  
  
  if(SDL_RenderCopy(r,t,NULL,&box)!=0)
    LOG<<SDL_GetError()<<std::endl;
}
