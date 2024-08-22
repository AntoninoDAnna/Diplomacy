#pragma once
#include "globals.h"
#include <iostream>
struct Unit{
  ID id;
  ID region_id;
  Units_types type;
  friend std::ostream& operator<<(std::ostream& os, const Unit& u);
};
