#ifndef TROOP_H
#define TROOP_H

#include <string>


class Troop{
  private: 
    int troop_type; // 1 =army 2 = fleet
    std::string region_abb;
    std::string owner_name;
  public:
    Troop(int type, std::string reg_abb, std::string owner);
    std::string get_troop();
    std::string get_owner();
    std::string get_region();
};

#endif
