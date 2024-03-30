#include "region.h"
#include "global_variables.h"
#include <string>
#include <list>

Region::Region(std::string name, std::string abb, std::list<int> neighbors, int id, bool is_sc, bool is_land, bool is_sea) :
name(name),
abbreviation(abb),
neighbors_id(neighbors),
id(id),
sc(is_sc),
land(is_land), 
sea(is_sea),
country_id(EMPTY_FIELD),
occupied(false),
new_unit_id(EMPTY_FIELD),
unit_id(EMPTY_FIELD)
{};

std::string Region::get_abbreviation()
{
  return abbreviation;
}

int Region::get_country_id()
{
  return country_id;
}

int Region::get_id()
{
  return id;
}

std::string Region::get_name(){
  return name;
}

const std::list<int>& Region::get_neighborlist()
{
  return neighbors_id;
}

bool Region::get_new_unit_id()
{
  return new_unit_id;
}

bool Region::get_unit_id()
{
  return unit_id;
}

bool Region::is_coast()
{
  return land&&sea;
};

bool Region::is_land() 
{
  return land;
}

bool Region::is_occupied()
{
  return occupied;
}
bool Region::is_sea()
{
  return sea;
}

bool Region::operator==(Region& r){
  return this->id == r.id;
}
