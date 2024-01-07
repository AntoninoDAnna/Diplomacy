#ifndef   GLOBAL_VARAIBLES_H
#define   GLOBAL_VARAIBLES_H

// logfile file and error messages
#include <fstream>
#include <map>
#include <string>
#include <list>
#include "troop.h"
#include "region.h"
#include "player.h"

inline std::ofstream  logfile;
inline constexpr int  NO_game_file = 01;
inline constexpr int  Invalid_game = 02;
inline constexpr int  Mistype_game_file = 03;
inline constexpr int  No_troop_type = 04;
inline constexpr int  Invalid_order_type = 05;
inline constexpr int  Troop_not_found = 06;

// global const 

inline const std::string  No_owner = "NO OWNER"; 
inline const std::string  No_region = "";
inline constexpr int  Army  = 1;
inline constexpr int  Fleet = 2;
inline constexpr int  Troop_movements = 3;
inline constexpr int  Buildings = 4;
// global varaibles 

inline std::map <std::string, Region>  table; // game table
inline std::map <std::string, Player>  players;
inline std::list <Troop>  troops;
inline int n_players;
inline int n_regions;



inline constexpr short  HOLD = 0;
inline constexpr short  ATTACK =1;
inline constexpr short  SUPPORT_HOLD = 2; 
inline constexpr short  SUPPORT_ATTACK = 3;
inline constexpr short  CONVOY = 4;
#endif