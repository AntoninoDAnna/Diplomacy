#pragma once

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "globals.h"
#include <SDL2/SDL.h>
class Region{
public:
  Region(const std::string& name,const std::string& abb, bool sc, bool land, bool sea, ID id);
  Region(const Region & R) = default;
  ~Region();
  std::string get_name()const{return m_name;};
  int get_id()const{return m_id;};
  int get_country_id()const{return m_country_id;};
  const std::list<int>& get_neighborlist()const{return m_neighbors;};
  std::string get_abbreviation()const{return m_abbr;};
  bool is_occupied()const{return m_occupied;};
  bool is_sea()const {return m_sea;};
  bool is_land()const{return m_land;};
  bool is_coast()const{return m_land && m_sea;};
  int get_unit_id()const{return m_unit_id;};
  void occupy(ID unit_id);
  void liberate(); 
  void update_unit_id(ID id){m_unit_id = id;};
  void update_country_id(ID id){m_country_id = id;};
  bool operator==(const Region& r);
  bool operator!=(const Region& r);
  friend std::ostream& operator<<(std::ostream & os, const Region&);
  void set_neighbors(const std::list<ID>& neigbors_id);
  void set_vertex(int x, int y);
private:
  const int NONE = 0;
  const std::string m_abbr;
  ID m_country_id = NONE;
  const ID m_id;
  const bool m_land;
  bool m_occupied = NONE;
  const bool m_sc;
  const bool m_sea;
  const std::string m_name;
  std::list<ID> m_neighbors;
  ID m_unit_id = NONE;
  SDL_FPoint tile_vertex{0,0};
};

