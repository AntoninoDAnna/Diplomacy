#pragma once

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "globals.hpp"
#include "button.hpp"
#include "resources_manager.hpp"
#include <SDL2/SDL.h>
class Region{
public:
  Region(const std::string& name,const std::string& abb, bool sc, bool land, bool sea, ID id);
  Region(const Region & R) = default;
  ~Region();
  std::string get_name()const{return m_name;};
  int get_id()const{return m_id;};
  int get_country_id()const{return m_country_id;};
  const std::list<int>& get_neighborlist()const{return m_neighbors;};
  std::string get_abbreviation()const{return m_abbr;};
  bool is_occupied()const{return m_occupied;};
  bool is_sea()const {return m_sea;};
  bool is_land()const{return m_land;};
  bool is_coast()const{return m_land && m_sea;};
  int get_unit_id()const{return m_unit_id;};
  void occupy(ID unit_id);
  void liberate(); 
  void update_unit_id(ID id){m_unit_id = id;};
  void update_country_id(ID id){m_country_id = id;};
  bool operator==(const Region& r);
  bool operator!=(const Region& r);
  friend std::ostream& operator<<(std::ostream & os, const Region&);
  void set_neighbors(const std::list<ID>& neigbors_id);

  template <class T,class R>
  void set_region_on_map(int x, int y, int w, int h, T window,R rm, std::ostream &log = std::cout);
  /* 
   * render the region rescaling the box to the window size. 
   * rw and rh are the scaling factor respectively for width and heigh.  
   */
  template <class T, class R>
  void render_region(T r, R rm,double rw, double rh,std::ostream &log = std::cout);

  template <class T, class R>
  Button make_button(T r,R rm,double rw, double rh);
  bool is_selected(int& x, int& y);
  void pressed();
  SDL_Rect get_box();
private: 
  SDL_Rect rescale_box(double rw, double rh);
private:
  const int NONE = 0;
  const std::string m_abbr;
  ID m_country_id = NONE;
  const ID m_id;
  const bool m_land;
  bool m_occupied = NONE;
  const bool m_sc;
  const bool m_sea;
  const std::string m_name;
  std::list<ID> m_neighbors;
  ID m_unit_id = NONE;
  SDL_Rect region_box{0,0,0,0};
};


template <class T,class R>
void Region::set_region_on_map(int x, int y, int w, int h,T window,R rm, std::ostream &log){
  static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>, "Error: window must be a (smart) pointer");
  static_assert(std::is_pointer_v<R> || Util::is_smart_pointer_v<R>, "Error: resource manager must be a (smart) pointer");
  region_box.x =x;
  region_box.y = y;
  region_box.w = w;
  region_box.h = h;
  rm->replace_texture(m_abbr,rm->get_file(m_abbr),window, log);
}

template <class T, class R>
void Region::render_region(T window,R rm, double rw, double rh,std::ostream&log){
  static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>, "Error: window must be a (smart) pointer");
  static_assert(std::is_pointer_v<R> || Util::is_smart_pointer_v<R>, "Error: resource manager must be a (smart) pointer");
  SDL_Rect box = rescale_box(rw,rh);
  window->render_copy(rm->get_texture(m_abbr,log),NULL,&box);
}

template <class T, class R>
Button Region::make_button(T window, R rm, double rw, double rh){
  static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>, "Error: window must be a (smart) pointer");
  static_assert(std::is_pointer_v<R> || Util::is_smart_pointer_v<R>, "Error: resource manager must be a (smart) pointer");
  SDL_Rect box = rescale_box(rw,rh);
  return Button(m_abbr,box,window,
                [this]()-> void {
                  std::cout <<this->get_name() << std::endl;
                }, rm);
}
