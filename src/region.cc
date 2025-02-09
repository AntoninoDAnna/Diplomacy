#include "../include/region.h"
#include "../include/log.h"
#include "../include/resources_manager.h"
#include "../include/button.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <list>

Region::Region(const std::string& name,const std::string& abb, bool sc, bool land, bool sea, ID id):
 m_abbr(abb),
 m_id(id),
 m_land(land),
 m_sc(sc),
 m_sea(sea),
 m_name(name)
{

}

Region::~Region(){
}

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


void Region::set_region_on_map(int x, int y, int w, int h,SDL_Renderer* r,Resources_Manager* rm){
  region_box.x =x;
  region_box.y = y;
  region_box.w = w;
  region_box.h = h;
  rm->replace_texture(m_abbr,rm->get_file(m_abbr),r);
}

void Region::render_region(SDL_Renderer*r,Resources_Manager* rm){
  SDL_RenderCopy(r,rm->get_texture(m_abbr),NULL,&region_box);
}


void Region::pressed(){
  LOG << m_abbr << std::endl;
}

bool Region::is_selected(int& x, int& y){
  if(x<=region_box.x)              return false;
  if(x>=region_box.x+region_box.w) return false;
  if(y<=region_box.y)              return false;
  if(y>=region_box.y+region_box.h) return false;
  return true;
}

Button Region::make_button(SDL_Renderer* r, Resources_Manager* rm){
  return Button(m_abbr,region_box,r,[this]()-> void {LOG << m_abbr << std::endl;}, rm);
}

SDL_Rect Region::get_box(){
  return region_box;
}


