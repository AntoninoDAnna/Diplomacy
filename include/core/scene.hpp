#pragma once

#include <string>
#include "event.hpp"
#include "context.hpp"

namespace Core{

  class Scene {
  public:
    Scene(const std::string name,Context* ctx) : name(name),m_context(ctx) {}
    virtual  ~Scene();
    virtual void on_event(Event& event);
    virtual void on_update();
    virtual void on_render();
    std::string get_name(){return name;}
  protected:
    Context* get_context(){return m_context;}
  private:
    std::string name;
    Context* m_context;
  };
  
}
