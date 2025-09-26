#include "color.hpp"
#include <initializer_list>
#include <string>
#include <log.hpp>
#include <sys/types.h>
#include "imgui.h"

namespace Core{
  Colour::Colour(const std::initializer_list <Uint8>& l) {
    r = *(l.begin()+0);
    b = *(l.begin()+1);
    g = *(l.begin()+2);
    a = *(l.begin()+3);
  };

  Colour::Colour(const SDL_Colour &sdl_c) {
    r = sdl_c.r;
    b = sdl_c.b;
    g = sdl_c.g;
    a = sdl_c.a;
  }

  Colour::Colour(const ImVec4 &v) {
    r = static_cast<Uint8>(v.x*255);
    b = static_cast<Uint8>(v.y*255);
    g = static_cast<Uint8>(v.z*255);
    a = static_cast<Uint8>(v.w*255);
  }


  Colour_map::Colour_map() {
    map.emplace(std::pair<Colours,Colour>{Colours::RED,Colour{255,0,  0,  255}});
    map.emplace(std::pair<Colours,Colour>{Colours::GREEN,Colour{0,  255,0,  255}});
    map.emplace(std::pair<Colours,Colour>{Colours::BLUE,Colour{0,  0,  255,255}});
    map.emplace(std::pair<Colours,Colour>{Colours::MENU,Colour{54, 220,215,255}});
    map.emplace(std::pair<Colours,Colour>{Colours::BACKGROUND,Colour{54, 220,215,255}});
    map.emplace(std::pair<Colours,Colour>{Colours::BLACK,Colour{0, 0, 0, 255}});
    map.emplace(std::pair<Colours,Colour>{Colours::NONE,Colour{0, 0, 0, 0}});
  }

  std::string col2str(const Colours c) {
    switch (c) {
    case Colours::RED :
      return "red";
      break;
    case Colours::BLUE :
      return "blue";
      break;
    case Colours::GREEN:
      return "green";
      break;
    case Colours::BACKGROUND :
      return "Background color";
      break;
    case Colours::WHITE:
      return "white";
      break;
    case Colours::BLACK:
      return "black";
      break;
    case Colours::MENU:
      return "Menu color";
      break;
    default:
      return "Missing color";
    }
  }


  Colour get_colour(Colours C, const Colour_map& cm) {
    if (cm.map.find(C) == cm.map.end()){
      LOGL("colour {} not found, Colours::NONE returned", col2str(C));
      return cm.map.at(Colours::NONE);
    }
    return cm.map.at(C);
  };
}
