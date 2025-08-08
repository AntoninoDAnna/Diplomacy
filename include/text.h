#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "resources_manager.h"
#include "window.h"
#include "utilities.h"
#include <string>
#include <memory>

class Text{
public:
  template <class T, class R>
  Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  T&  w, R& resources,std::ostream& log=std::cout);
  private:
    std::string text;
};

template <class T,class R>
Text::Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  T& window, R& rm, std::ostream& log):
text(text) {

  if(rm->haskey_texture(text)){
    window->render_copy(rm->get_texture(text),NULL,&box,log);
    return;
  }

  SDL_Surface* s = TTF_RenderText_Solid(font,text.c_str(),color);

  if(s==NULL)
    LOG<<SDL_GetError()<<std::endl;

  SDL_Texture* t =  window->create_texture_from_surface(s);

  SDL_FreeSurface(s);

  if(!t)
    LOG<<SDL_GetError()<<std::endl;

  rm->add_texture(text,t);

  window->render_copy(t,NULL,&box,log);;
}
