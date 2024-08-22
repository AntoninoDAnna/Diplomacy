#include "../include/region.h"

int main(){
  Region test("test","test",false,false,true,78);
  std::cout << test.is_sea()<<std::endl;
  std::cout << test<<std::endl;
}