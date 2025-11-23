

#pragma once 
#include "SDL2/SDL.h"
#include <functional>
#include <string>
#include "window.hpp"
#include "manager.hpp"
#include "context.hpp"

namespace Core{ 

  template <class RetT, class... ArgsT>
  class BButton{
  public:
    BButton(const std::string& key, SDL_Rect& rect,std::function<RetT(ArgsT...)> fun, Context* ctx);
    BButton(const BButton<RetT,ArgsT...>& B) = default;
    virtual ~BButton()=default;
    virtual bool pressed(int, int)=0;    
    std::function<RetT(ArgsT...)> action;

  protected:
    std::string m_texture_key{};
    SDL_Rect m_rect{};
  };
  
  template <class RetT,class... ArgsT>
  class Rect_Button : public BButton<RetT, ArgsT...>{
  public:
    Rect_Button(const std::string& key, SDL_Rect& rect, std::function<RetT(ArgsT...)> fun, Context* ctx) : BButton<RetT,ArgsT...>(key,rect,fun,ctx) {};
    Rect_Button() = default;
    Rect_Button(const Rect_Button<RetT,ArgsT...>& B);
    
    bool pressed(int mous_x, int mouse_y) override;
    std::function<RetT(ArgsT...)> action;
  };

  template class Rect_Button<void>;
  typedef Rect_Button<void> Button;
  

}

