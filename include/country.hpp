#pragma once
#include <string>
#include <list>
#include "globals.hpp"
#include "unit.hpp"

class Country{
public:
  Country(std::string name,std::list<int> hsc,int id, std::list<ID> unit_it);
  void add_sc(int region_id);
  void remove_sc(int region_id); 
  std::string string() const ;
  size_t get_nunits() const { return m_unit_id.size(); }
private:
  const int m_id; //
  const std::list<int> m_hsc; //
  const std::string m_name; //
  std::list<int> m_sc; //
  std::list<int> m_this_turn_orders; // non in creation
  std::list<ID> m_unit_id; //
};


std::ostream& operator<<(std::ostream & os , const Country& );
