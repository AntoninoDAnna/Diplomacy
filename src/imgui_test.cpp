#include "devel_tool.cc"


int main(int, char**){

  Devel_app = devel_app;
  devel_app.init();
  devel_app.start();
  return 0;
}
