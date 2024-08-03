#include "../include/game.h"
#include "../include/region.h"
#include <string>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <vector>

Game::Game(std::string game) :
LOG(std::fstream("log.log"))
{
  read_file("map_info"/std::filesystem::path(game)/".txt");
  start_game(game);
}

Game::~Game()
{
}

void Game::read_file(std::filesystem::path path){
  std::ifstream game_file(path);
  LOG << "Preparing table ..."<<std::endl;

 /*   game_file is organized as follow:
  *  n_region = number of regions;
  *  Region name; region abbreviation; isSupplyCenter;	isLand;	isSea;	Neigbhors list;
  */

  int n_regions;
  game_file>> n_regions;
  next_line(game_file);
  next_line(game_file);
  std::vector<std::string> temp_split_line;
  std::string tline;
  for(int line = 0; line<n_regions; line++){
    std::getline(game_file,tline);

  }



}

std::string strip_trailing_ws(std::string t){
  if(std::isspace(t.back())){ 
    t.pop_back();
    return strip_trailing_ws(t);
  }
  return t;
}

void split_line(const std::string line, const char separator=';'){
  std::vector<std::string> v;
  std::string t;
  for(char c : line){
    if(c==separator){
      v.push_back(strip_trailing_ws(t));
      t.clear();
    }
    else if(c == ' '){
      if(t.size()!=0){
        if(std::isspace(t.back())) continue;
        else t.push_back(c);
      }
      else continue;
    }
    else if (std::isspace(c)) continue;
    else t.push_back(c);
  }


}

void next_line(std::ifstream& file){
  std::string temp;
  std::getline(file, temp);
  return;
}

//   std::vector<std::string> temp_split_line;
//   std::string temp_line, name, abbr;
//   bool is_sc, is_land, is_sea;
//   std::list<std::string> neighbors;

//   for(int line =0; line <n_regions; line++)
//   {
//     std::getline(game_file, temp_line);
//     split_line(temp_line,temp_split_line);

//     name = temp_split_line[0];
//     abbr = temp_split_line[1];
//     is_sc = (temp_split_line[2]=="0")? true:false;
//     is_land = (temp_split_line[3]=="0")? true:false;
//     is_sea = (temp_split_line[4]=="0")? true:false;
    
//     for(unsigned int i =5; i<temp_split_line.size(); i++)
//     {
//       neighbors.push_back(temp_split_line[i]);
//     }
//     temp_split_line.clear();
//     table.insert({abbr,Region(name,abbr,is_sc,is_land,is_sea,neighbors)});
//     neighbors.clear();
//     logfile << "Extracted region "<< name << std::endl;
//   }

//   skip_line(game_file);

//   game_file>> n_players;
//   logfile << "Expecting "<< n_players << " players" << std::endl;
//   skip_line(game_file);  skip_line(game_file);
//   int troop_type;
//   std::string temp;
//   std::list<std::string> sc_list;
//   for(int line=0; line<n_players; line++)
//   {
//     std::getline(game_file, temp_line);
//     split_line(temp_line,temp_split_line);
//     name = temp_split_line[0];
//     for(unsigned int i=1; i<temp_split_line.size(); i+=2)
//     {
//       abbr = temp_split_line[i];
//       sc_list.push_back(abbr);
//       table.at(abbr).change_owner(name);
//       temp = temp_split_line[i+1];
//       if(temp=="Army") troop_type = Army;
//       else if(temp == "Fleet") troop_type = Fleet;
//       else
//       {
//         logfile << "ERROR: mistype in game file";
//         exit(Mistype_game_file);
//       }
//       temp.clear();
//       troops.push_back(Troop(troop_type,abbr,name));

//     }
//     // players[name]=Player(name,sc_list);
//     players.insert({name, Player(name,sc_list)});
//     logfile << "Extracted player "<< name << std::endl;
//     name.clear();
//     sc_list.clear();
//     temp_line.clear();
//     temp_split_line.clear();
//   }
//   game_file.close();


// }