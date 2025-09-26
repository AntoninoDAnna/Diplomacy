#include "app_scene.hpp"

std::unique_ptr<Core::Scene> make_scene(Scene_id id){
  switch(id){
  case Scene_id::NONE:
    return nullptr;
    break;
  case Scene_id::MAIN_MENU:
    return std::make_unique<MainMenu>();
    break;
  case Scene_id::NEW_GAME:
    return std::make_unique<NewGame>();
    break;
  case Scene_id::G
  }
}
