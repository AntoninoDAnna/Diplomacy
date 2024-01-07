#include <iostream>
#include <string>
#include "global_variables.h"
#include "troop.h"

Troop::Troop(int type, std::string reg_abb,std::string owner){
  if(type!= Army &&type!=Fleet){
    logfile << "Error: Invalid troop type while constructing a troop in ";
    logfile << reg_abb << " for "<< owner<<std::endl;
    logfile << "Troop type in input is: "<< type<<std::endl; 
    exit(No_troop_type);
  }
  this->troop_type = type;
  this->region_abb = reg_abb;
  this->owner_name = owner;  
}

std::string Troop::get_troop(){
  if(troop_type == Army) return "Army";
  return "Fleet";
}
std::string Troop::get_region(){ return region_abb;}
std::string Troop::get_owner(){  return owner_name;}