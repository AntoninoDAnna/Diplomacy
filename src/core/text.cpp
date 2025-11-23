#include "text.hpp"

namespace Core{
  Text::Text(const std::string& text, const SDL_Color color, SDL_Rect& box,  Context* ctx) :
    text(text) {
    if(ctx->m_manager.haskey_texture(text)){
      ctx->m_window.render_copy(ctx->m_manager.get_texture(text),NULL,&box);
      return;
    }

    SDL_Surface* s = TTF_RenderText_Solid(ctx->m_font,text.c_str(),color);

    if(s==NULL)
      LOGL(SDL_GetError());

    SDL_Texture* t =  ctx->m_window.create_texture_from_surface(s);

    SDL_FreeSurface(s);

    if(!t)
      LOGL(SDL_GetError());

    ctx->m_manager.add_texture(text,t);

    ctx->m_window.render_copy(t,NULL,&box);
  }
}
