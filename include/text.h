#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "resources_manager.h"
#include <string>

class Text{
  public:
    Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  SDL_Renderer* r, Resources_Manager* resources);
    Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  SDL_Renderer* r, Resources_Manager& resources);
  private:
    std::string text;
};