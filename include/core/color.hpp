#ifndef COLOR_H_
#define COLOR_H_

#include <SDL2/SDL_pixels.h>
#include <initializer_list>
#include <unordered_map>
#include "SDL2/SDL.h"
#include <string>
#include "imgui.h"

namespace Core{
  struct Colour {
    Uint8 r, b, g, a;
    //Colour()= default;
    Colour(const std::initializer_list<Uint8>&);
    Colour(const SDL_Color& );
    Colour(const ImVec4&);

    operator SDL_Color() const { return {r, g, b, a}; };

    operator ImVec4() const {
      return {r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f};
    };

  };


  enum class Colours {RED, BLUE, GREEN, BACKGROUND, WHITE, BLACK, MENU, NONE};

  class Colour_map {
  public:
    Colour_map();
    ~Colour_map()=default;
    friend Colour get_colour(Colours, const Colour_map&);

  private:
    std::unordered_map<Colours,Colour> map;
  };

  inline Colour_map cmap;

  Colour get_colour(Colours,const Colour_map& cm = cmap);
  std::string col2str(Colour C);
}
#endif // COLOR_H_
