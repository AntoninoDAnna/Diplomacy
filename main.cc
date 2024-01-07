#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include "diplomacy_functions.h"

#include "player.h"
#include "troop.h"
#include "utilities.h"
#include "global_variables.h"
#include "order.h"



using std::cout, std::endl, std::cin;

int main(){
  logfile.open("log.txt");
  // To fix when implementing GUI
  /*
  cout << "WELCOME TO DIPLOMACY"<<endl;
  cout << "Select game mode"<<endl;
  cout << "\t - classic game: 0" << endl;
  cout << "\t - gunboat game: 1" << endl;
  cout << "\t - sandbox game: 2" << endl;
  int game_mode;
  do{
    cin>> game_mode;
    logfile << "Selected game mode "<< game_mode << endl;
    if(game_mode<0 || game_mode>2){
      cout << "Invalid game mode" <<endl;
    }
  }while(game_mode<0||game_mode>2);

  cout << "Select the map:"<< endl;

  cout << "Classic Map: 0"<<endl;
  cout << "Ancient Mediterrean: 1"<< endl;

  int game_map;
  do{
    cin>> game_map;
    logfile << "Selected map "<< game_map << endl;
    switch (game_map)
    {
    case 0:
      cout << "Unfortunately, this map is not available, yet"<< endl;
      cout << "Why don't you try Ancient Mediterrean?"<< endl;
      logfile << "Invalid map, map setted to 1" << endl;
      game_map = 1;
      break;
    case 1:
      cout << "Loading map Ancient Mediterrean"<< endl;
      break;
    default:
      cout << "Invalid map" << endl;
      break;
    }
    
    
  }while (game_map<0 ||game_map>1);
  */

  prepare_table(1);


  // print_table();




  logfile.close();
}
