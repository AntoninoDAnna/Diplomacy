#include "button.hpp"
#include "manager.hpp"
#include <memory>

namespace Core{
  template <class ReturnType, class... ArgsType>
  _Button<ReturnType, ArgsType...>::_Button(
					    const std::string &key, SDL_Rect &rect, std::shared_ptr<Window> &w,
					    std::function<ReturnType(ArgsType...)> action,
					    std::shared_ptr<Manager> &rm)
    : action(action), m_texture_key(key), m_rect(rect){

    w->render_copy(rm->get_texture(key),NULL,&m_rect);
  }


  template <class ReturnType,class... ArgsType>
  _Button<ReturnType,ArgsType...>::_Button(const _Button<ReturnType,ArgsType...>& B) :
    action(B.action),m_texture_key(B.m_texture_key),m_rect(B.m_rect){}

  template <class ReturnType,class... ArgsType>
  void _Button<ReturnType,ArgsType...>::operator=(const _Button<ReturnType,ArgsType...>& B){
    this->m_texture_key = B.m_texture_key;
    this->m_rect = B.m_rect;
    this->action = B.action;
  }


  template <class ReturnType,class... ArgsType>
  bool _Button<ReturnType,ArgsType...>::pressed(int mouse_x, int mouse_y){
    if(mouse_x< m_rect.x) return false;
    if(mouse_x> m_rect.x+m_rect.w) return false;
    if(mouse_y< m_rect.y) return false;
    if(mouse_y> m_rect.y+ m_rect.h) return false;
    return true;
  }

  template class _Button<void>;
}
