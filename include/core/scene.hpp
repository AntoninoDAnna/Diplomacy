#pragma once

#include <string>
#include "event.hpp"
#include "window.hpp"

namespace Core{

  class Scene {
  public:
    Scene(const std::string name) : name(name) {}
    virtual  ~Scene() = default;
    virtual void on_event(Event& event){}
    virtual void on_update(){}
    virtual void on_render(){}
    std::string get_name(){return name;}
  private:
    std::string name;
  };
}
