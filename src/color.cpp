#include "color.hpp"
#include <string>
#include <log.hpp>

Color_map::Color_map(){
  map[Color::RED]  = SDL_Color{255, 0, 0, 255};
  map[Color::GREEN]= SDL_Color{0, 255, 0, 255};
  map[Color::BLUE] = SDL_Color{0, 0, 255, 255};
  map[Color::MENU] = SDL_Color{54, 220, 215, 255};
  map[Color::BACKGROUND] = SDL_Color{54,220,215,255};
  map[Color::BLACK]= SDL_Color{0, 0, 0, 255};
}

std::string col2str(const Color c) {
  switch (c) {
  case Color::RED :
    return "red";
    break;
  case Color::BLUE :
    return "blue";
    break;
  case Color::GREEN:
    return "green";
    break;
  case Color::BACKGROUND :
    return "Background color";
    break;
  case Color::WHITE:
    return "white";
    break;
  case Color::BLACK:
    return "black";
    break;
  case Color::MENU:
    return "Menu color";
    break;
  default:
    return "Missing color";
  }
}


SDL_Color get_color(Color C, Color_map cm) {
  if (cm.map.find(C) == cm.map.end())
    LOGL("[Color_map]: color {} not found", col2str(C));
  return cm.map.at(C);
};
