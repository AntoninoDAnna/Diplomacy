#include "country.hpp"
#include <stdexcept>
#include <iostream>
#include <format>


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

std::string Country::string() const{
  std::string res;
  res = std::format("Country name:        {}\n", m_name);
  res+= std::format("Country ID:          {}\n", m_id);
  res += "Home  supply Centers ";
  for(int id : m_hsc)
    res += std::format("{} ", id);
  res += "\n";
  res +="Supply Centers:      ";
  for(int id : m_sc)
   res += std::format("{} ", id);
  res +="\n";

  res+=std::format("The country has {} units\n", get_nunits());
  res+="Unit id:  ";
  for(auto id: m_unit_id)
   res += std::format("{} ", id);
  res +="\n";
  return res;
}

std::ostream& operator<<(std::ostream & os , const Country& C){
  os << C.string();
  return os;
}

