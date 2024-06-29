#include "diplomacy.h"
#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <random>

Table table_game;
using std::cout, std::endl;
typedef std::pair<int,int> unit_loc;

int main(){
  std::random_device rd;
  std::mt19937 id_gen(rd());
  int por_id = id_gen();
  int spa_id = id_gen();
  int MID_id = id_gen();
  int gas_id = id_gen();
  int mar_id = id_gen();
  int GOL_id = id_gen();
  int WES_id = id_gen();
  std::list<int> spa_neighbor = {por_id,MID_id,gas_id,mar_id,GOL_id,WES_id};
  std::list<int> por_neighbor = {MID_id,spa_id};

  table_game.emplace(Table_entry(spa_id, Region("spain","spa",spa_neighbor,spa_id,1,1,1)));
  table_game.emplace(Table_entry(por_id, Region("portugal","por",por_neighbor,por_id,1,1,1))); 

  int por_fleet_id = id_gen();
  int spa_army_id = id_gen();
  int Iberia_id = id_gen();
  cout << "gonna construct iberia"<<endl;
  Country Iberia = Country("Iberia",std::list<int>{por_id,spa_id},Iberia_id,std::list<unit_loc>{unit_loc{por_fleet_id,por_id},unit_loc{spa_army_id, spa_id}},table_game);
  return 0;
}