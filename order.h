#ifndef ORDER_H
#define ORDER_H
#include <string>
#include <list>
#include "global_variables.h"

struct Order
{

  int troop_type = 0;
  int order_type = 0;
  bool is_legal = true;
  bool succeded = true;
  std::string where = No_region;
  std::string from = No_region;
  std::string to = No_region;


  Order(int troop, std::string where, int type = HOLD); // hold constructor
  Order(int troop, std::string from, std::string to); // attack constructor;
  Order(int troop, std::string where, int type, std::string from, std::string to);// support to attack and convoy
  Order(int troop, std::string where, int type, std::string from); // support in hold;

};


typedef std::list<Order> orders_list;
inline  orders_list this_turn_orders_list;



#endif