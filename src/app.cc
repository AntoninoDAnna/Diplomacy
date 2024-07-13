#include "../include/app.h"
#include <iostream>

App::App(){
  std::cout << "Creating app"<< std::endl;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(640*2,480*2,0,&window,&renderer);
  SDL_RenderSetScale(renderer,2,2);
}

App::~App(){
  std::cout << "Deleting app" << std::endl;

}

void App::pixel(float x, float y){
  SDL_FPoint P;
  P.x = x;
  P.y = y;
  points.emplace_back(P);
} 

void App::show(){
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer,255,255,255,255);
  for(auto& point : points){
    SDL_RenderDrawPointF(renderer,point.x,point.y);
  }
  SDL_RenderPresent(renderer);
}

void App::input(){
  while(SDL_PollEvent(&e)){
    if(e.type ==SDL_QUIT){
      SDL_Quit();
      exit(0);
    }
  }
}
void App::clear(){
  points.clear();     
}

SDL_FPoint App::center(){
  int w,h;
  SDL_GetWindowSize(window,&w,&h);
  SDL_FPoint P{w/4.0f,h/4.0f};
  return P;
}