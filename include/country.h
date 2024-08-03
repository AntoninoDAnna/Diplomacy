#pragma once
#include <string>
#include <list>
// #include "region.h"

struct Unit_position{
  int unit_id;
  int region_id;
  Unit_position(int, int);
};

class Country{
public:
  Country(std::string name,std::list<int> hsc,int id, std::list<Unit_position> unit_loc);
  void add_sc(int region_id);
  void remove_sc(int region_id); 
  friend std::ostream& operator<<(std::ostream & os , const Country& );

private:
  const int id; //
  const std::list<int> hsc; //
  const std::string name; //
  std::list<int> sc; // 
  std::list<int> this_turn_orders; // non in creation
  std::list<Unit_position> unit_position; //
  int n_unit;
};
