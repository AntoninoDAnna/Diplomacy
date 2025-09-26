#pragma once

#include <list>
#include <iostream>
#include <string>
#include "globals.hpp"
#include "button.hpp"
#include <SDL2/SDL.h>

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
  template <class T,class R>
  void set_region_on_map(int x, int y, int w, int h, T window,R rm);
  /*
   * render the region rescaling the box to the window size.
   * rw and rh are the scaling factor respectively for width and heigh.
   */
  template <class T, class R>
  void render_region(T r, R rm, double rw, double rh);

  template <class T, class R>
  Button make_button(T r, R rm, double rw, double rh);

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


template <class T,class R>
void Region::set_region_on_map(int x, int y, int w, int h,T window,R rm){
  static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>, "Error: window must be a (smart) pointer");
  static_assert(std::is_pointer_v<R> || Util::is_smart_pointer_v<R>, "Error: resource manager must be a (smart) pointer");
  region_box.x =x;
  region_box.y = y;
  region_box.w = w;
  region_box.h = h;
  rm->replace_texture(m_abbr,rm->get_file(m_abbr),window);
}

template <class T, class R>
void Region::render_region(T window,R rm, double rw, double rh){
  static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>, "Error: window must be a (smart) pointer");
  static_assert(std::is_pointer_v<R> || Util::is_smart_pointer_v<R>, "Error: resource manager must be a (smart) pointer");
  SDL_Rect box{rescale_box(rw,rh)};
  window->render_copy(rm->get_texture(m_abbr),NULL,&box);
}

template <class T, class R>
Button Region::make_button(T window, R rm, double rw, double rh){
  static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>, "Error: window must be a (smart) pointer");
  static_assert(std::is_pointer_v<R> || Util::is_smart_pointer_v<R>, "Error: resource manager must be a (smart) pointer");
  SDL_Rect box{rescale_box(rw,rh)};
  return Button(m_abbr,box,window,
                [this]()-> void {
                  std::cout <<this->get_name() << std::endl;
                }, rm);
}
