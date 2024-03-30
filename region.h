#ifndef REGION_H
#define REGION_H

#include <list>
#include <string>

class Region{
private:
  const std::string abbreviation;
  int country_id;
  const int id;
  const bool land;
  bool occupied;
  const bool sc;
  const bool sea;
  const std::string name;
  const std::list<int> neighbors_id;
  int new_unit_id;
  int unit_id;
  
public:
  Region(std::string name,std::string abb, std::list<int> neighbors, int id, bool is_sc, bool is_land, bool is_sea);
  std::string get_name();
  int get_id();
  int get_country_id();
  const std::list<int>& get_neighborlist();
  std::string get_abbreviation();
  bool is_occupied();
  bool is_sea();
  bool is_land();
  bool is_coast();
  bool get_unit_id();
  bool get_new_unit_id();

  bool operator==(Region& r);

};



#endif