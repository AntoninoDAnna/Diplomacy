#include "../include/region.h"
#include "../include/log.h"
#include "../include/resources_manager.h"
#include "../include/button.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <list>
#include <fstream>

Region::Region(const std::string& name,const std::string& abb, bool sc, bool land, bool sea, ID id):
 m_abbr(abb),
 m_id(id),
 m_land(land),
 m_sc(sc),
 m_sea(sea),
 m_name(name)
{

}

Region::~Region(){}

bool Region::operator==(const Region& r){
  return this->m_id == r.m_id;
}

bool Region::operator!=(const Region& r){
  return !(this->operator==(r));
}


std::ostream& operator<<(std::ostream & os , const Region& R){
  os << "Region name:         "<< R.m_name <<std::endl;
  os << "Region abbreviation: "<< R.m_abbr<< std::endl;
  os << "Region ID:           "<< R.m_id << std::endl;        
  
  if(R.m_sc)
    os << "Is supply center"<<std::endl;
  else
    os << "Is NOT supply center"<<std::endl;

  os << "Country:             ";
  if(R.m_country_id)
    os << R.m_country_id << std::endl;
  else
    os << "None"<< std::endl;
  os << "Geography:           " << std::endl;
  os << "  coast:             " << R.is_coast() << std::endl;
  os << "  land:              " << R.m_land     << std::endl;
  os << "  sea:               " << R.m_sea      << std::endl;
  os << "Neighbors list:      ";
  for(int id : R.m_neighbors) 
    os << id << " ";
  os << std::endl;

  if(R.m_occupied)
    os<< "The region is ocupied by: " << R.m_unit_id << std::endl;
  else
    os<< "The region is free"<< std::endl;
  return os;
}

void Region::set_neighbors(const std::list<ID>& neighbors){
  for(ID n : neighbors)
    m_neighbors.push_back(n);
}

void Region::occupy(ID id){
  m_occupied = true;
  m_unit_id = id;
}

void Region::liberate(){
  m_occupied=false;
  m_unit_id=NONE;
}

SDL_Rect Region::rescale_box(double rw, double rh){
  return SDL_Rect{static_cast<int>(region_box.x*rw),
                  static_cast<int>(region_box.y*rh),
                  static_cast<int>(region_box.w*rw),
                  static_cast<int>(region_box.h*rh)};
}

void Region::pressed(){
  std::cout << m_abbr << std::endl;
}

bool Region::is_selected(int& x, int& y){
  if(x<=region_box.x)              return false;
  if(x>=region_box.x+region_box.w) return false;
  if(y<=region_box.y)              return false;
  if(y>=region_box.y+region_box.h) return false;
  return true;
}


SDL_Rect Region::get_box(){
  return region_box;
}

