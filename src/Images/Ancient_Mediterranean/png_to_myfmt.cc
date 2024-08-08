#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <iterator>
#include <bit>
#include <numeric>
#include <numbers>
#include <cstring>


using Bytes = std::vector<std::byte>;
Bytes PNG_Header = {std::byte(0x89),
                    std::byte(0x50),
                    std::byte(0x4E),
                    std::byte(0x47),
                    std::byte(0x0D),
                    std::byte(0x0A),
                    std::byte(0x1A),
                    std::byte(0x0A)};

bool check_header(Bytes& buffer){
  for(int i =0; i<8; i++){
    if(buffer[i]!=PNG_Header[i]) return false;
  }
  return true;
}

void read_IHDR(Bytes& buffer, std::vector<int>& IHDR){
  u_int32_t length;
  std::memcpy(&length,buffer.data()+10, 1);
  std::cout << length << std::endl;
};
void convert_to_myfmt(const char* filename){
  std::ifstream file(filename, std::ios::binary);
  file.seekg(0,std::ios::end);
  auto size = file.tellg();
  file.seekg(0,std::ios::beg);
  Bytes buffer(size);
  file.read(reinterpret_cast<char*>(&buffer[0]),size);
  buffer.resize(file.tellg());
  file.close();

  if(!check_header(buffer)){
    std::cout << "header check failed. skipping file"<<std::endl;
    return;
  }
  std::vector<int> IHDR(7);
  read_IHDR(buffer,IHDR);
  return;
}

int main(int narg, char** arg){
  if(narg==1){
    std::cout<< "you need to specify a png file";
    exit(1);
  }
  for(int i =1; i<narg; i++){
    std::filesystem::path filename = arg[i];
    if(filename.extension().compare(".png")!=0){
      std::cout << filename << " is not a png file, conversion skipped"<<std::endl;
      continue;
    }
    convert_to_myfmt(arg[i]);  
  }
  return 0;
}