#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <list>
class Player{

private:
  std::string state_name;
  std::list<std::string> home_sc;
  std::list<std::string> supply_centre;
  int troop_num;
  bool is_playing;
public:
  Player(std::string name, std::list<std::string> supply_centre);
void send_orders(int order_type);
};

#endif