#include "region.h"
#include "global_variables.h"
#include <string>
#include <list>

Region::Region() : 
  abbreviation(""),
  country_id(EMPTY_FIELD),
  id(EMPTY_FIELD),
  land(false), 
  _occupied(false),
  sc(),
  sea(false),
  name(""),
  neighbors_id(),
  new_unit_id(EMPTY_FIELD),
  unit_id(EMPTY_FIELD)
{};

Region::Region(std::string name, std::string abb, std::list<int> neighbors, int id, bool is_sc, bool is_land, bool is_sea) :
  abbreviation(abb),
  country_id(EMPTY_FIELD),
  id(id),
  land(is_land), 
  _occupied(false),
  sc(is_sc),
  sea(is_sea),
  name(name),
  neighbors_id(neighbors),
  new_unit_id(EMPTY_FIELD),
  unit_id(EMPTY_FIELD)
{};

Region::Region(const Region &R) :
  abbreviation(R.abbreviation),
  country_id(R.country_id),
  id(R.id),
  land(R.land), 
  _occupied(R._occupied),
  sc(R.sc),
  sea(R.sc),
  name(R.name),
  neighbors_id(R.neighbors_id),
  new_unit_id(R.new_unit_id),
  unit_id(R.unit_id)
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

int Region::get_new_unit_id()
{
  return new_unit_id;
}

int Region::get_unit_id()
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
  return _occupied;
}
bool Region::is_sea()
{
  return sea;
}

bool Region::operator==(const Region& r){
  return this->id == r.id;
}

bool Region::operator!=(const Region& r){
  return !(this->operator==(r));
}

void Region::update_unit_id(int id){
  this->unit_id = id;
}
void Region::update_country_id(int id){
  this->country_id = id;
}

void Region::occupied(){ _occupied = true;};

std::ostream& operator<<(std::ostream & os , const Region& R){
  os << "Region name:         "<< R.name <<std::endl;
  os << "Region abbreviation: "<< R.abbreviation<< std::endl;
  os << "Region ID:           "<< R.id << std::endl;        
  os << "Country:             ";
  if(R.country_id)
    os << R.country_id << std::endl;
  else
    os << "None"<< std::endl;
  os << "Geography            ";

  if(R.land){
    if(R.sea) os << "Coast" << std::endl;
    else os << "Land"<<std::endl;
  }else if(R.sea) os << "Sea"<< std::endl;
  else os << "Non accessible region" << std::endl;
  
  os << "Neighbors list:      ";
  for(int id : R.neighbors_id) 
    os << id << " ";
  os << std::endl;

  if(R._occupied)
    os<< "The region is ocupied by: " << R.unit_id << std::endl;
  else
    os<< "The region is free"<< std::endl;
  return os;
}
