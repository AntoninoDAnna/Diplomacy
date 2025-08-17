#include "sdl_wrap.hpp"
#include <iostream>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

void init_SDL(SDL_WindowFlags wf) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    std::cerr <<"Error in initiating SDL, aborting" << std::endl;
    //m_log << "[App: start()]" << SDL_GetError()<< std::endl;
    exit(EXIT_FAILURE);
  }

  if(TTF_Init() == -1){
    std::cerr << "Error in initializing TTF, aborting"<< std::endl;
    // m_log << "[App: start()]" << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  };

  if(IMG_Init(IMG_INIT_PNG) ==0){
    std::cerr << "Error in initializing PNG, aborting"<< std::endl;
    // m_log << "[App: start()]" << IMG_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
}
