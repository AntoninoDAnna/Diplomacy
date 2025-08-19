#ifndef COLOR_H_
#define COLOR_H_

#include <SDL2/SDL_pixels.h>
#include <unordered_map>
#include "SDL2/SDL.h"
#include <string>

enum class Color { RED, BLUE, GREEN, BACKGROUND, WHITE, BLACK, MENU };

class Color_map {
  public:
  Color_map();
  ~Color_map()=default;
  friend SDL_Color get_color(Color, Color_map);

private:
  std::unordered_map<Color,SDL_Color> map;
};

inline Color_map cmap;

SDL_Color get_color(Color,Color_map cm = cmap);
std::string col2str(Color C);
#endif // COLOR_H_
