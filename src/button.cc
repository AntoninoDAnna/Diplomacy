#include <iostream>
#include "../include/button.h"
#include "../../SDL/include/SDL.h"
#include "../../SDL/include/SDL_image.h"

Button::Button(int x, int y, int w, int h, const  char* file, SDL_Renderer* r) :
rect(SDL_Rect{x,y,w,h}), surf(IMG_Load(file)), texture(SDL_CreateTextureFromSurface(r, surf)){
  SDL_RenderCopy(r, texture, NULL,&rect);
}

Button::~Button(){
  SDL_FreeSurface(surf);
  SDL_DestroyTexture(texture);
}

bool Button::pressed(int mouse_x, int mouse_y){
  if(mouse_x< rect.x) return false;
  if(mouse_x> rect.x+rect.w) return false;
  if(mouse_y< rect.y) return false;
  if(mouse_y> rect.y+ rect.h) return false;
  return true;
}
