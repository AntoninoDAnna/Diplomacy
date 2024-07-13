#ifndef APP_H
#define APP_H
#include "../../SDL/include/SDL.h"
#include <vector>
class App{

public: 
  App();
  ~App();
  void pixel(float x, float y);
  void show();
  void input();
  void clear();
  SDL_FPoint center();
private:
  SDL_Event e;
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::vector<SDL_FPoint> points;
  
};

#endif