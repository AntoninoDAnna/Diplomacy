#include "region.hpp"
#include "log.hpp"
#include "resources_manager.hpp"
#include "button.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <immintrin.h>
#include <pthread.h>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

Region::Region(const std::string &name, const std::string &abb, uint32_t f,
               ID id)
    : m_abbr(abb), m_id(id), m_flag(f | Region_Flags::RENDER), m_name(name) {}

Region::~Region() {}

bool Region::operator==(const Region &r) { return this->m_id == r.m_id; }

bool Region::operator!=(const Region &r) { return !(this->operator==(r)); }

std::string Region::get_details() const {
  std::stringstream str{};
  str << "Region name:         "<< m_name <<std::endl;
  str << "Region abbreviation: "<< m_abbr<< std::endl;
  str << "Region ID:           "<< m_id << std::endl;

  if(is_sc())
    str << "Is supply center"<<std::endl;
  else
    str << "Is NOT supply center"<<std::endl;

  str << "Country:             ";
  if(m_country_id!=NONE)
    str << m_country_id << std::endl;
  else
    str << "None"<< std::endl;

  str << "Geography:           " << std::endl;
  str << "  coast:             " << is_coast() << std::endl;
  str << "  land:              " << is_land()  << std::endl;
  str << "  sea:               " << is_sea()   << std::endl;
  str << "Neighbors list:      ";
  for(int id : m_neighbors)
    str << id << " ";
  str << std::endl;

  if(!is_free())
    str<< "The region is ocupied by: " << m_unit_id << std::endl;
  else
    str << "The region is free" << std::endl;

  str << "The region is ";
  if (!is_rendered())
    str << "not ";
  str << "rendered" << std::endl;

  return str.str();
}

std::ostream &operator<<(std::ostream &os, const Region &R) {
  os << R.get_details();
  return os;
}

void Region::occupy(ID id) {
  set_flag(Region_Flags::OCCUPIED);
  m_unit_id = id;
}

void Region::freed(){
  unset_flag(Region_Flags::OCCUPIED);
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

bool Region::is_selected(int x, int y) const{
  if(x<=region_box.x)              return false;
  if(x>=region_box.x+region_box.w) return false;
  if(y<=region_box.y)              return false;
  if(y>=region_box.y+region_box.h) return false;
  return true;
}

bool Region::is_sc() const { return m_flag & Region_Flags::SC; }

bool Region::is_sea() const { return m_flag & Region_Flags::SEA; }

bool Region::is_land() const { return m_flag & Region_Flags::LAND; }

bool Region::is_coast() const {
  return m_flag & (Region_Flags::SEA | Region_Flags::LAND);
}

bool Region::is_free() const { return !is_occupied(); }

bool Region::is_occupied() const { return m_flag & Region_Flags::OCCUPIED; }

std::string Region::get_abbreviation() const { return m_abbr; }

int Region::get_country_id() const { return m_country_id; }

int Region::get_id() const { return m_id; }

std::string Region::get_name() const { return m_name; }

const std::list<int> &Region::get_neighborlist() const { return m_neighbors; }

int Region::get_unit_id() const { return m_unit_id; }

SDL_Rect Region::get_box() const { return region_box; }

void Region::conquered(ID country_id) { m_country_id = country_id; }

void Region::set_neighbors(std::list<ID> neighbors) {
  if (m_neighbors.size() != 0)
    LOGL("HEY! your resetting the neighbor list of {}, m_name");
  m_neighbors.swap(neighbors);
}

bool Region::is_rendered() const { return m_flag & Region_Flags::RENDER; }
void Region::set_render_flag() { m_flag |= Region_Flags::RENDER; }
void Region::unset_render_flag() {m_flag &= ~Region_Flags::RENDER; }
void Region::set_flag(uint32_t flag) { m_flag |= flag; }
void Region::unset_flag(uint32_t flag) { m_flag &= ~flag; }
