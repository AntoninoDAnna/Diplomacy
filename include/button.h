#pragma once 
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <functional>
#include <string>

class Button{

  public:
    Button(const std::string& key, SDL_Rect rect, SDL_Renderer* r, std::function<void()> action);
    bool pressed(int mouse_x, int mouse_y);
    std::function<void()> action;
  private:
    std::string m_texture_key;
    SDL_Rect m_rect;


};
