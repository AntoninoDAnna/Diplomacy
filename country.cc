#include "country.h"
#include "global_variables.h"
#include <stdexcept>
#include <iostream>

Country::Country(std::string name,std::list<int> hsc, int id,std::list<std::pair<int,int>>unit_loc, Table &table) :
  id(id),
  hsc(hsc),
  name(name),
  sc(hsc),
  this_turn_orders(),
  unit_location(unit_loc),
  n_unit(unit_loc.size())
{
  int unit_id,territory_id;
  for(auto UL : unit_location){
    unit_id = UL.first;
    territory_id=UL.second;
    if(table.count(territory_id) == 0)
      std::cerr << "Error: territory_id not found while looking creating Country "<< name<< std::endl;

    Region& aux_R = table.at(territory_id);
    aux_R.update_unit_id(unit_id);
    aux_R.occupied();
    aux_R.update_country_id(id);
  } 
};

std::ostream& operator<<(std::ostream & os , const Country& C){
  os << "Country name:        " << C.name << std::endl;
  os << "Country ID:          " << C.id << std::endl;
  os << "Home supply Centers: ";
  for(int id : C.hsc)
    os << id << "  ";
  
  os << "Supply Centers:      ";
  for(int id : C.sc)
    os << id << "  ";
  os << "The country has " << C.n_unit<< " units"<<std::endl;
  os << "Unit location:       "<< std::endl;
  for(auto [unit_id,region_id] : C.unit_location)
    os << "\t\t unit: "<< unit_id << "in "<< region_id<< std::endl;

  return os;
}
