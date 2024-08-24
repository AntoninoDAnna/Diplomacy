#pragma once 
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <functional>
#include <string>


template <class ReturnType> 
class _Button{
  public:
    _Button(const std::string& key, SDL_Rect& rect, SDL_Renderer* r, std::function<ReturnType()> action);
    _Button() = default;
    _Button(const _Button<ReturnType>& B);
    void operator=(const _Button<ReturnType>& B);
    bool pressed(int mous_x, int mouse_y);
    std::function<ReturnType()> action;
  private:
    std::string m_texture_key;
    SDL_Rect m_rect; 
};

typedef _Button<void> Button;