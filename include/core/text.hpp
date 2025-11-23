#pragma once

#include <string>
#include "SDL2/SDL_ttf.h"
#include "core.hpp"

namespace Core{
  class Text{
  public:
    Text(const std::string& text, const SDL_Color color, SDL_Rect& box,  Context* ctx);
  private:
    std::string text;
  };
}
