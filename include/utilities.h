#pragma once

#include <filesystem>
#include <vector>
/* 
  parse a tile txt file. the file is a representation in '0' '1' '2' of the tile's pixels.
  it is better to make a png file of the tile and the generate the txt file automatically with
  png_to_myfmt.jl 
  'outline' and 'inside' are filled with bool value where value correspond to a pixel on the outline/inside 
 */


namespace Util{
  void parse_tile(std::filesystem::path filepath,std::vector<bool>& outline,std::vector<bool>&inside);
}