#include "devel_tool.h"


int main(int, char**){
  App app;
  Devel_app devel_app(app);
  devel_app.init();
  devel_app.start();
  return 0;
}
