#include "country.hpp"
#include <stdexcept>
#include <iostream>



Country::Country(std::string name,std::list<int> hsc, int id,std::list<ID>unit_id) :
  m_id(id),
  m_hsc(hsc),
  m_name(name),
  m_sc(hsc),
  m_this_turn_orders(),
  m_unit_id(unit_id)
{};

void Country::add_sc(int region_id){
  m_sc.push_back(region_id);
}

void Country::remove_sc(int region_id){
  m_sc.remove(region_id);
}

std::ostream& operator<<(std::ostream & os , const Country& C){
  os << "Country name:        " << C.m_name << std::endl;
  os << "Country ID:          " << C.m_id << std::endl;
  os << "Home supply Centers: ";
  for(int id : C.m_hsc)
    os << id << ", ";
  os << std::endl;
  os << "Supply Centers:      ";
  for(int id : C.m_sc)
    os << id << ", ";
  os << std::endl;
  os << "The country has " << C.get_nunits() << " units"<<std::endl;
    os << "Unit id:  "<< std::endl;
  for(auto id: C.m_unit_id)
    os << id  << " ";
  os<< std::endl;
  return os;
}

