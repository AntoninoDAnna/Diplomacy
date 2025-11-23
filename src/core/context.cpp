#include "SDL2/SDL_ttf.h"
#include "core.hpp"

namespace Core{
  Context::~Context(){
    m_window.close();
    TTF_CloseFont(m_font);
    SDL_Quit();
  }
  
 void Context::init(uint32_t flag){
    LOGL("Initializing Context");
    init_SDL(flag);
    m_font = TTF_OpenFont(font_path.c_str(),16);
    if(m_font ==nullptr){
      LOGL("Error: font not loaded: {}",TTF_GetError());
      exit(EXIT_FAILURE);
    }
 }
  
  void Context::init_window(const char* title, uint32_t flag){
    m_window.init(title,flag);
  }

  
}
