#pragma once 
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <functional>
#include <memory>
#include <string>
#include "resources_manager.hpp"
#include "window.hpp"

template <class ReturnType,class... ArgsType>
class _Button{
  public:
    _Button(const std::string& key, SDL_Rect& rect, std::shared_ptr<Window>& w, std::function<ReturnType(ArgsType...)> action, std::shared_ptr<Resources_Manager>& rm);

    //_Button(const std::string& key, SDL_Rect& rect, SDL_Renderer* r, ReturnType (*action)(ArgsType...), Resources_Manager& rm);
    //_Button(const std::string& key, SDL_Rect& rect, SDL_Renderer* r, ReturnType (*action)(ArgsType...), Resources_Manager *rm);
    _Button() = default;
    _Button(const _Button<ReturnType,ArgsType...>& B);
    void operator=(const _Button<ReturnType,ArgsType...>& B);
    bool pressed(int mous_x, int mouse_y);
    std::function<ReturnType(ArgsType...)> action;
  private:
    std::string m_texture_key{};
    SDL_Rect m_rect{}; 
};

typedef _Button<void> Button;
