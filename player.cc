#include <string>
#include <list>
#include <vector>
#include <sstream>
#include "global_variables.h"
#include "utilities.h"
#include "player.h"

Player::Player(std::string name, std::list <std::string> sc){
  this->state_name = name;
  this->is_playing=true;
  this->troop_num =0;
  for(std::string x: sc){
    this->home_sc.push_back(x);
    this->supply_centre.push_back(x);
    this->troop_num++;
  }
}
/* 
void Player::send_orders(int order_type){
  // da sistemare una volta inserita la gui
  std::string given_order;

  switch (order_type)
  {
  case Troop_movements:
    std::cout << "Player: " << state_name << std::endl;
    std::cout << "Your troops are: "<<std::endl;
    for(int i=0; i<troop_num; i++){
        std::cout << 
    }


    break;
  case Buildings:
    break;
  default:
    logfile << "Wrong order type given to Player " << state_name << std::endl;
    exit(Invalid_order_type);
    break;
  }

   /*
  input format: 
  HOLD:           troop_type region_where_is_now H 
  ATTACK:         troop_type region_where_is_now - region_attacked 
  SUPPORT_HOLD    troop_type region_where_is_now S region_supported H
  SUPPORT_ATTACK  troop_type region_where_is_now S region_supported - region_attacked
  COVOY           F          sea_where_is_now    C costal_region_from - costal_region_to (can convoy only armies);
  */
  

  /*
  stored order:
  check_int actual_order;


  */

