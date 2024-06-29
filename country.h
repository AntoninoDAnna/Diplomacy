#ifndef COUNTRY_H
#define COUNTRY_H
#include <string>
#include <list>
#include "region.h"
class Country{
private:
  const int id; //
  const std::list<int> hsc; //
  const std::string name; //
  std::list<int> sc; // 
  std::list<int> this_turn_orders; // non in creation
  std::list<std::pair<int,int>> unit_location; //
  int n_unit;
// Users
  void inser_one_order();
  void confirm_single_order(int order_id);

public:
  Country(std::string name,std::list<int> hsc,int id, std::list<std::pair<int,int>> unit_loc, Table &table);
  void inser_orders();
  void view_order();
  void change_order(int order_id);
  void send_orders();
  void add_to_sc(int region_id);
  void remove_from_sc(int region_id); 
  friend std::ostream& operator<<(std::ostream & os , const Country& );

};



#endif