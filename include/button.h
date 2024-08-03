#pragma once 
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Button{
  public:
    Button(int x, int y, int w, int h, const char* file, SDL_Renderer* r);
    ~Button();
    bool pressed(int mouse_x, int mouse_y);
    
  private: 
    SDL_Rect rect;
    SDL_Surface *surf;
    SDL_Texture *texture; 
};
