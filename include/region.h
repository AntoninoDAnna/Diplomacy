#pragma once

#include <list>
#include <iostream>
#include <string>
#include <unordered_map>

class Region{
public:
  Region(std::string name,std::string abb, std::list<int> neighbors, int id, bool is_sc, bool is_land, bool is_sea);
  Region(const Region & R);
  Region();
  std::string get_name();
  int get_id();
  int get_country_id();
  const std::list<int>& get_neighborlist();
  std::string get_abbreviation();
  bool is_occupied();
  bool is_sea();
  bool is_land();
  bool is_coast();
  int get_unit_id();
  int get_new_unit_id();
  void occupied();
  void update_unit_id(int id);
  void update_country_id(int id);
  bool operator==(const Region& r);
  bool operator!=(const Region& r);
  friend std::ostream& operator<<(std::ostream & os, const Region&);

private:
  const int NONE = 0;
  const std::string abbreviation;
  int country_id;
  const int id;
  const bool land;
  bool _occupied;
  const bool sc;
  const bool sea;
  const std::string name;
  const std::list<int> neighbors_id;
  int new_unit_id;
  int unit_id;
};

// struct Table_entry
// {
//   int id;
//   Region& R; 
// };


typedef std::pair<int,Region> Table_entry;
typedef std::unordered_map<int,Region> Table;
