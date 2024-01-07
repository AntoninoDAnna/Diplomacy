#ifndef REGION_H
#define REGION_H

#include <iostream>
#include <string>
#include <list>

class Region{

private:
  std::string name;
  std::string abbreviation;
  bool is_supply_center;
  bool is_land;
  bool is_sea;
  std::list<std::string> neighbors;
  std::string owner;
public:
  Region(std::string name, std::string abb, 
        bool is_supply_center, bool is_land, bool is_sea, 
        std::list<std::string>& neighbors_region);
  bool can_go(int troop_type);
  void change_owner(std::string owner_name);
  bool are_neighbor(Region U);
  bool get_land();
  bool get_sea();
  bool get_coast();
};

#endif