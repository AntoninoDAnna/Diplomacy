#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <string>
#include <vector>

void skip_line(std::fstream& file);
void split_line(std::string str, std::vector <std::string> &res,const char token=';' );

#endif