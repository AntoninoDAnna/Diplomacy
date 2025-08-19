#ifndef SCENES_HPP_
#define SCENES_HPP_

#include <iostream>
#include <string>

enum class Scene_id{NONE, MAIN_MENU, NEW_GAME,GAME};

inline std::string scene2str(Scene_id scene) {
  switch(scene){
  case Scene_id::NONE :
    return "NONE";
    break;
  case Scene_id::MAIN_MENU :
    return "MAIN MENU";
    break;
  case Scene_id::NEW_GAME :
    return "NEW GAME";
    break;
  case Scene_id::GAME :
    return "GAME";
    break;
  default:
    return "NOT KNOWN";
    break;
  }
}
inline std::ostream& operator<<(std::ostream& os, Scene_id s){
  os << scene2str(s);
  return os;
}



#endif // SCENES_H_
