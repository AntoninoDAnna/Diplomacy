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

  template <class T>
  struct is_smart_pointer : std::false_type {};

  template <class T>
  struct is_smart_pointer<std::unique_ptr<T>> : std::true_type{};

  template <class T>
  struct is_smart_pointer<std::shared_ptr<T>> : std::true_type{};

  template <class T>
  struct is_smart_pointer<std::weak_ptr<T>> : std::true_type{};

  template <class T>
  constexpr bool is_smart_pointer_v = is_smart_pointer<T>::value;

  void parse_tile(std::filesystem::path filepath,std::vector<bool>& outline,std::vector<bool>&inside);
  std::string strip_trailing_ws(std::string t);
  std::vector<std::string> split_line(const std::string& line, const char separator=';');
  void next_line(std::ifstream& file, int nline=1);
}
