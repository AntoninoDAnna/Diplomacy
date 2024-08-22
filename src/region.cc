#include "../include/region.h"
#include "../include/log.h"
#include "../include/file_manager.h"
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
  g_FILES.remove(m_abbr);
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

void Region::set_vertex(int x, int y){
  tile_vertex.x =x;
  tile_vertex.y =y;
}