#include "sdl_wrap.hpp"
#include <iostream>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "log.hpp"

void init_SDL(SDL_WindowFlags wf) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
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
