#include "app.hpp"

int main(){
  App app;
  app.init();
  std::cout << "ok"<< std::endl;
  app.open();
  std::cout << "ok"<< std::endl;
  return 0;
}
