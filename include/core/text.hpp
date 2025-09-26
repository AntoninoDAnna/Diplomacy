#pragma once

#include <string>
#include "SDL2/SDL_ttf.h"
#include "core.hpp"

namespace Core{
  class Text{
  public:
    template <class T, class R>
    Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  T&  w, R& resources);
  private:
    std::string text;
  };

  template <class T,class R>
  Text::Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  T& window, R& rm):
    text(text) {
    static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>,
		  "Error: window must be a (smart) pointer");
    static_assert(std::is_pointer_v<R> || Util::is_smart_pointer_v<R>,
		  "Error: resources manager  must be a (smart) pointer");

    if(rm->haskey_texture(text)){
      window->render_copy(rm->get_texture(text),NULL,&box);
      return;
    }

    SDL_Surface* s = TTF_RenderText_Solid(font,text.c_str(),color);

    if(s==NULL)
      LOGL(SDL_GetError());

    SDL_Texture* t =  window->create_texture_from_surface(s);

    SDL_FreeSurface(s);

    if(!t)
      LOGL(SDL_GetError());

    rm->add_texture(text,t);

    window->render_copy(t,NULL,&box);
  }
}
