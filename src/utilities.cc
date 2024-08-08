#include "../include/utilities.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
void parse_tile(std::filesystem::path filepath,std::vector<bool>& outline,std::vector<bool>&inside){
  std::ifstream file(filepath,std::ios::in);
  outline.clear();
  inside.clear();
  std::string c;
  while(!file.eof()){
    file >> c;
    std::cout << c<< std::endl;
    for(auto x : c){
      if(x == '0'){
        outline.push_back(false);
        inside.push_back(false);
      } else if(x == '1'){
        outline.push_back(true);
        inside.push_back(false);
      } else if(x == '2'){
        outline.push_back(false);
        inside.push_back(true);
      }
    }
  }
}