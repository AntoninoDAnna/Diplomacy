#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "texture_manager.h"
#include <string>

class Text{
  public:
    Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  SDL_Renderer* r );
  private:
    std::string text;
};