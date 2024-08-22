#include "../include/unit.h"

std::ostream& operator<<(std::ostream& os, const Unit& u){
  os << "Unit ID:  "<< u.id<< std::endl;
  os << "Region ID:"<< u.region_id<<std::endl;
  os << "Type ID:  ";
  if(u.type == Units_types::FLEET)
    os << "Fleet"<<std::endl;
  else if(u.type ==Units_types::ARMY)
    os << "Army" << std::endl;
  else
    os << "No type"<<std::endl;
  return os;
} 
