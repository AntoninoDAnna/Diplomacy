#include <string>
#include "order.h"
#include "global_variables.h"

Order::Order(int troop, std::string T1,int type){ // hold
  this-> troop_type = troop;
  this-> where = T1;
  this-> order_type = type; 
  if(type == HOLD){   
    is_legal = true;
    succeded = true;
    return;
  }
  logfile << "ERROR: submitted order as a hold with invalid order typer" << std::endl;
  exit(Invalid_order_type);
}

 Order::Order(int troop, std::string T1, std::string T2){ //attack
  this-> troop_type = troop;
  this-> from = T1;
  this-> to = T2;
  this-> order_type = ATTACK;
  if(table.at(T1).are_neighbor(table.at(T2))&&table.at(T2).can_go(troop)){
    is_legal = true;
    succeded =true;
    return;
  } 
  is_legal =false;
  succeded =false;
}

Order::Order(int troop, std::string T1, int type, std::string T2, std::string T3){ // support attack or convoy
  this-> troop_type = troop;
  this-> where = T1;
  this-> order_type = type;
  this-> from  = T2;
  this-> to = T3;
  if(type = SUPPORT_ATTACK){
    if(table.at(T1).are_neighbor(table.at(T3))&&table.at(T2).are_neighbor(table.at(T3))
        &&table.at(T2).can_go(troop)){
      is_legal=true;
      succeded =true;
    }
    is_legal=false; 
    succeded=false;
    return;
  } 
  if(type== CONVOY){
    if( troop==Fleet && table.at(T2).get_coast() && table.at(T3).get_coast())
    {
      is_legal=true;
      succeded=true;
    }
    is_legal=false; 
    succeded=false;
    return;
  } 
  logfile << "ERROR: submitted order as a support on attack or convoy with invalid order typer" << std::endl;
  exit(Invalid_order_type);
}

Order::Order(int troop, std::string T1, int type, std::string T2){
  this-> troop_type = troop;
  this-> where = T1;
  this-> order_type = type;
  this-> to = T2;
  if(type==SUPPORT_HOLD)
  {
    if(table.at(T1).are_neighbor(table.at(T2))&&table.at(T2).can_go(troop)){
      is_legal=true;
      succeded=true;
      return;
    }
    is_legal = false;
    succeded = false;
  } 
  logfile << "ERROR: submitted order as a support hold with invalid order typer" << std::endl;
  exit(Invalid_order_type);
} // support in hold;