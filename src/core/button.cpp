#include "button.hpp"
#include "manager.hpp"
#include "window.hpp"
#include "context.hpp"

namespace Core{

  template <class RetT, class... ArgsT>
  BButton<RetT,ArgsT...>::BButton(const std::string& key, SDL_Rect& rect,std::function<RetT(ArgsT...)> fun, Context* ctx) :
    action(fun), m_texture_key(key), m_rect(rect){
    ctx->m_window.render_copy(ctx->m_manager.get_texture(m_texture_key),
			      NULL,&m_rect );  
  }  

  template <class RetT, class... ArgsT>
  Rect_Button<RetT,ArgsT...>::Rect_Button(const Rect_Button<RetT,ArgsT...>& B)
    : BButton<RetT,ArgsT...>(B){}
  
  template <class RetT,class... ArgsT>
  bool Rect_Button<RetT,ArgsT...>::pressed(int mouse_x, int mouse_y){
    if(mouse_x< this->m_rect.x) return false;
    if(mouse_x> this->m_rect.x + this->m_rect.w) return false;
    if(mouse_y< this->m_rect.y) return false;
    if(mouse_y> this->m_rect.y + this->m_rect.h) return false;
    return true;
  }
}
