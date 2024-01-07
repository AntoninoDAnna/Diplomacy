#include <iostream>
#include <string>
#include "global_variables.h"
#include "region.h"

Region::Region(std::string name, std::string abb, 
        bool is_SC, bool is_land, bool is_sea,
        std::list<std::string>& neighbor_list)
{
  name = name;
  abbreviation = abb;
  is_supply_center=is_SC;
  is_land = is_land;
  is_sea = is_sea;
  for(std::string x : neighbor_list)
      neighbors.push_back(x); 
  owner = No_owner;
}

bool Region::are_neighbor(Region U)
{
  for(std::string x : this->neighbors)
  for(std::string y : U.neighbors)
      if(x.compare(y) == 0 ) return true; 
  return false;
}

bool Region::can_go(int troop_type){
  if(troop_type==Army) return is_land;
  return is_sea;
}

void Region::change_owner(std::string owner_name){
  owner = owner_name;
}
bool Region::get_coast(){
  return is_land&&is_sea;
}
bool Region::get_land(){
  return is_land;
}
bool Region::get_sea(){
  return is_sea;
}