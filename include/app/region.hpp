#pragma once

#include <list>
#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "core.hpp"

typedef int ID;

enum Region_Flags {
  LAND = 0x01,
  SEA = 0x02,
  SC = 0x04,
  OCCUPIED = 0x08,
  RENDER = 0x10
};

class Region {
public:
  Region(const std::string& name, const std::string& abb, uint32_t f,  ID id);
  Region(const Region & R) = default;
  ~Region();

  // getters
public:
  std::string get_abbreviation() const;
  SDL_Rect get_box() const;
  int get_country_id() const;
  std::string get_details() const;
  int get_id() const;
  std::string get_name() const;
  const std::list<int> &get_neighborlist() const;
  int get_unit_id() const;

  // setter
public:
  void set_neighbors(const std::list<ID> neigbhors);
  void set_render_flag();
  void unset_render_flag();
  // state query
public:
  bool is_sea() const;
  bool is_land() const;
  bool is_coast() const;
  bool is_free() const;
  bool is_occupied() const;
  bool is_sc() const;
  bool is_rendered() const;

  // update region state
  void occupy(ID unit_id);
  void freed();
  void conquered(ID country_id);

  // operator overloading
  bool operator==(const Region& r);
  bool operator!=(const Region& r);
  friend std::ostream& operator<<(std::ostream & os, const Region&);

  // rendering functioons
  void set_region_on_map(int x, int y, int w, int h, Core::Context *ctx);
  /*
   * render the region rescaling the box to the window size.
   * rw and rh are the scaling factor respectively for width and heigh.
   */
  void render_region(double rw, double rh, Core::Context *ctx);

  Core::Button make_button(double rw, double rh,Core::Context *ctx);

  // interactions
  bool is_selected(int x, int y) const;
  void pressed();
  friend class Devel_tool;
private: // private functions
  SDL_Rect rescale_box(double rw, double rh);
  void set_flag(uint32_t flag);
  void unset_flag(uint32_t flag);

private: // Region data
  const int NONE = 0;
  const std::string m_abbr;
  ID m_country_id = NONE;
  const ID m_id;
  uint32_t m_flag;
  const std::string m_name;
  std::list<ID> m_neighbors;
  ID m_unit_id = NONE;
  SDL_Rect region_box{0,0,0,0};
};


