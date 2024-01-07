#include <fstream>
#include <string>
#include <vector>
#include "global_variables.h"
#include "utilities.h"

void  skip_line (std::fstream& file){
  // logfile << "skipping line"<< std::endl;
  std::string buff;
  std::getline(file,buff);
  buff.clear();
}
void  split_line(std::string str, std::vector <std::string> &res, const char token){
  // logfile << "splitting line "<< str << std::endl;
  std::string temp;
  for(char x :str){
    switch (x)
    {
    case ';':
      if(token!=';') temp.push_back(x);
      if(temp.size()==0) break;
      res.push_back(temp);
      temp.clear();
      break;
    case ' ':
      if(token==' '){
        if(temp.size()==0) break;
        res.push_back(temp);
        temp.clear();
      }
      else{
        if(temp.size() == 0) break;
        if(temp.back() == ' ') break;
        temp.push_back(x);
      }
      break;
    case '\t': break;
    case '\n': break;
    case '-':
      if(temp.size()==0){
        res.push_back("-");
        break;
      }
      if(temp.back()==' '){
        temp.pop_back();
        res.push_back(temp);
        res.push_back("-");
        temp.clear();
        break;
      }
      res.push_back(temp);
      res.push_back("-");
      temp.clear();    

    default:
      temp.push_back(x);
      break;
    }
  }
  if(temp.size()>1)  res.push_back(temp);
  
  /* logfile << "the lined as been splitte as :"<<std::endl;
  for(std::string x : res){
    logfile << x << std::endl;
  } */

}