#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "window.hpp"
#include "manager.hpp"
#include "SDL2/SDL_ttf.h"

namespace Core{
  class Context{
  public:
    Context() = default;
    ~Context();
    Window  m_window{};
    void init_window(const char* title,uint32_t flag);
    void init(uint32_t flags);

    TTF_Font* m_font = nullptr;;
    Manager m_manager{};
  };
  
}

#endif
