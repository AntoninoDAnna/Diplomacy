#ifndef COLOR_H_
#define COLOR_H_

#include <SDL2/SDL_pixels.h>
#include <unordered_map>
#include "SDL2/SDL.h"

enum class Color { RED, BLUE, GREEN, BACKGROUND, WHITE, BLACK, MENU };

class Color_map {
  public:
  Color_map();
  ~Color_map();
  SDL_Color get_color(Color);

private:
  std::unordered_map<Color,SDL_Color> map;
};

Color_map::Color_map() {
  map[Color::RED]  = SDL_Color{255, 0, 0, 255};
  map[COlor::GREEN]= SDL_Color{0, 255, 0, 255};
  map[Color::BLUE] = SDL_Color{0, 0, 255, 255};
  map[Color::MENU] = SDL_Color{54, 220, 215, 255};
  map[Color::BACKGROUND]

}

#endif // COLOR_H_
