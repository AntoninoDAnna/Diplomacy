#include "../include/country.h"
#include <stdexcept>
#include <iostream>


Unit_position::Unit_position(int unit_id, int region_id) :
  unit_id(unit_id), region_id(region_id){};


Country::Country(std::string name,std::list<int> hsc, int id,std::list<Unit_position>unit_loc) :
  id(id),
  hsc(hsc),
  name(name),
  sc(hsc),
  this_turn_orders(),
  unit_position(unit_loc),
  n_unit(unit_loc.size())
{};
void Country::add_sc(int region_id){
  sc.push_back(region_id);
}
void Country::remove_sc(int region_id){
  sc.remove(region_id);
}
std::ostream& operator<<(std::ostream & os , const Country& C){
  os << "Country name:        " << C.name << std::endl;
  os << "Country ID:          " << C.id << std::endl;
  os << "Home supply Centers: ";
  for(int id : C.hsc)
    os << id << ", ";
  os << std::endl;
  os << "Supply Centers:      ";
  for(int id : C.sc)
    os << id << ", ";
  os << std::endl;
  os << "The country has " << C.n_unit<< " units"<<std::endl;
    os << "Unit location:       "<< std::endl;
  for(auto  U: C.unit_position)
    os << "         unit:       "<< U.unit_id << "in "<< U.region_id<< std::endl;
  return os;
}
