#include "scene.hpp"
#include "log.hpp"
namespace Core{
  Scene::~Scene() = default;

  void Scene::on_render(){
    LOGL("No \"on_render()\" override provided");
  }

  void Scene::on_event(Event&){
    LOGL("No \"on_event(Core::Event&)\" override provided");
  }

  void Scene::on_update(){
    LOGL("no \"on_update()\" override provided");
  }
}
