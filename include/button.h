#pragma once 
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <functional>
class Button{
  public:
    Button(int x, int y, int w, int h, const char* file, SDL_Renderer* r, void(*action)());
    Button(SDL_Rect& rect, const char* file, SDL_Renderer* r,void(*action)());
    ~Button();
    bool pressed(int mouse_x, int mouse_y);
    void (*action)();
  private: 
    SDL_Rect m_rect;
    SDL_Surface *m_surf;
    SDL_Texture *m_texture; 
};
