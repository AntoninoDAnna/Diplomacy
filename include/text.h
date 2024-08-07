#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string>

class Text{
  public:
    Text(TTF_Font* font, const std::string& text, const SDL_Color color, SDL_Rect& box,  SDL_Renderer* r );
    ~Text();
  private:
    SDL_Surface* m_surf;
    SDL_Texture* m_texture;
};