#include "../include/utilities.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

namespace Util{
void parse_tile(std::filesystem::path filepath,std::vector<bool>& outline,std::vector<bool>&inside){
  std::ifstream file(filepath,std::ios::in);
  outline.clear();
  inside.clear();
  std::string c;
  while(!file.eof()){
    file >> c;
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

std::string strip_trailing_ws(std::string t){
  if(std::isspace(t.back())){ 
    t.pop_back();
    return strip_trailing_ws(t);
  }
  return t;
}

std::vector<std::string> split_line(const std::string& line, const char separator){
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
 
  return v;
}

void next_line(std::ifstream& file, int nline){
  std::string temp;
  for(int i =0; i<nline; i++) 
    std::getline(file, temp);
  return;
}
}