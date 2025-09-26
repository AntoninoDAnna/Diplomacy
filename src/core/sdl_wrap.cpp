#include "sdl_wrap.hpp"
#include <iostream>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "log.hpp"

void init_SDL(Uint32 wf) {
    if(SDL_Init(wf) != 0) {
    LOGL("Error in initializing SDL: {}", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  if(TTF_Init() == -1){
    LOGL("Error in initializing TTF: {}", SDL_GetError());
    exit(EXIT_FAILURE);
  };

  if(IMG_Init(IMG_INIT_PNG) ==0){
    LOGL("Error in initializing IMG: {}", IMG_GetError());
    exit(EXIT_FAILURE);
  }
}
