#include "game.hpp"
#include "region.hpp"
#include "country.hpp"
#include "resources_manager.hpp"
#include "log.hpp"
#include "utilities.hpp"
#include "unit.hpp"
#include "globals.hpp"
#include "button.hpp"
#include "text.hpp"
#include "window.hpp"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>
// #include <print>
class ID_gen{
  public:
    ID_gen(int seed) : m_seed(seed){}
    ID_gen() = default; 
    ID operator()(){
      ID old = m_seed;
      m_seed++;// update id generator
      return old; 
    }
  private:
  ID m_seed = 1;
};

ID_gen g_id = ID_gen();

Game::Game(){
  m_log.open("../bin/log/game_log.log", std::ios_base::out);
  if(!m_log.is_open()){
    std::cerr << "[Game(): cannot open log file. ABORTING"<<std::endl;
    exit(EXIT_FAILURE);
  }
  m_log << "Opening game log"<<std::endl;
}

void Game::set_pointers(std::shared_ptr<Window>& w, std::shared_ptr<Resources_Manager> &r){
  m_window = w;
  m_resources = r;
}
Game::~Game(){
  m_log << "closing for destruction of Game instance"<<std::endl;
  m_log.close();
}

void Game::start(Game_map& game){
  m_log << "[Game: start_game()] starting game" << std::endl;
  switch(game){
    case Game_map::ANCIENT_MEDITERREAN:
      m_gamename = g_AM;
      break;
    default:
      std::cerr<<"Game error: Undefined game map"<<std::endl;
      m_log<<"Game error: Undefined game map"<<std::endl;
      exit(1);
      break;
  }
  m_log << "[Game: start_game()] game: "<< m_gamename<<std::endl;
  m_log << "[Game: start_game()] updatig g_TILES file in m_resources"<< std::endl;
  m_resources->replace_file(g_TILES,img_folder/m_gamename/tiles_file,m_log);
  m_log << "[Game: start_game()] updatig g_MAP file in m_resources"<< std::endl;
  m_resources->replace_file(g_MAP,img_folder/m_gamename/(m_gamename+".png"),m_log);
  m_log << "[Game: start_game()] updatig g_MAP texture in m_resources"<< std::endl;
  m_resources->replace_texture(g_MAP,m_resources->get_file(g_MAP),m_window,m_log);
  read_map(m_resources->get_file(m_gamename,m_log));
  render_table();
  m_running = true;
  while(m_running){
    get_input();
  }
}

ID Game::get_region_ID(const std::string& abb){
  m_log << "[Game: get_region_ID()] searcing for region " << abb << std::endl;
  for(auto& [ID,R] : m_table){
    if(R.get_abbreviation().compare(abb)==0)
      return ID;
  }
  m_log << "[Game: get_region_ID()] search failed "<< std::endl;
  exit(1);
}

void Game::read_map(const std::filesystem::path& filename){
  m_log << "[Game: read_map()] reading map in path "<< filename << std::endl;
  std::ifstream file(filename,std::ios::in);
  int n_tile;
  file >> n_tile;  
  Util::next_line(file,2);  
  std::string file_line;
  std::vector<std::string> fields_name;
  bool sc,land,sea;
  ID id;
  // fill the table
  m_log << std::boolalpha;
  for(int i=0; i<n_tile; i++){
    std::getline(file,file_line); 
    // name abbreviation sc land sea   
    fields_name = Util::split_line(file_line);
    id = g_id();
    sc = std::stoi(fields_name[2]);
    land = std::stoi(fields_name[3]);
    sea  = std::stoi(fields_name[4]);
    m_table.emplace(id,Region(fields_name[0],fields_name[1],sc,land,sea,id));

    m_resources->add_file(fields_name[1],img_folder/m_gamename/tiles_folder/(fields_name[0]+".png"),m_log);
  }
  m_log << "[Game: read_map()] All Regions read" << std::endl;
  // read the neigbhors.
  Util::next_line(file);
  std::list<ID> neighbors;
  for(int i=0; i<n_tile; i++){
    std::getline(file, file_line);
    fields_name = Util::split_line(file_line);
    Region* current_R = &m_table.at(get_region_ID(fields_name[0]));
    
    for(size_t i=1; i<fields_name.size(); i++){
      neighbors.push_back(get_region_ID(fields_name[i]));
    }
    current_R->set_neighbors(neighbors);
    neighbors.clear();
  }
  m_log << "[Game: read_map()] All neighbors set"<< std::endl;
  // read the Country
  int n_country;
  file >> n_country;
  Util::next_line(file,2);
  std::list<ID> hsc;
  std::list<ID> units;
  Units_types type;
  for(int i =0; i< n_country; i++){
    std::getline(file, file_line);
    fields_name = Util::split_line(file_line);
    id = g_id();
    ID id_r, unit_id;
    for(size_t i=1; i<fields_name.size(); i+=2){
      id_r = get_region_ID(fields_name[i]);
      hsc.push_back(id_r);
      type = fields_name[i+1] == "Army" ? Units_types::ARMY : Units_types::FLEET;
      unit_id = g_id();
      m_units.emplace(unit_id,Unit{unit_id,hsc.back(),type});
      units.push_back(unit_id);
      m_table.at(id_r).is_occupied();
    }
    m_countries.emplace(id,Country(fields_name[0],hsc,id,units));
    hsc.clear();
    units.clear();
  }
  m_log << "[Game: read_map()] All Countries set" << std::endl;
  
  file.close();
  
  file.open(m_resources->get_file(g_TILES,m_log),std::ios::in);
  Util::next_line(file);
  int x,y,w,h;
  file >> x >> x >> m_board_w >> m_board_h;
  std::string abb;
  
  
  while(!file.eof()){
    file >> abb >> x >> y >> w >> h;
    id = get_region_ID(abb);
    m_table.at(id).set_region_on_map(x,y,w,h,m_window,m_resources, m_log);
  }

  file.close();
  return;
}

void Game::close_game(){
  m_running = false;
  m_log<< "[Game: close_game] closing game" << std::endl;
  m_table.clear();
  m_log << "[Game: close_game] table cleared"<<std::endl;
  m_countries.clear();
  m_log << "[Game: close_game] countries cleared" << std::endl;
  m_units.clear();
  m_log << "[Game: close_game] units cleared"<< std::endl;
};

void Game::render_table(){
  m_log << "[Game: render_table] rendering table"<<std::endl;
  m_log << "[Game: render_table] clearing buttons"<< std::endl;
  m_buttons.clear();
  m_log << "[Game: render_table] resetting rendering"<< std::endl;
  m_window->reset_rendering();
  m_log << "[Game: render_table] rendering map"<< std::endl;
  m_window->render_copy(m_resources->get_texture(g_MAP),NULL,NULL,m_log);

  int w,h;
  m_window->get_renderer_size(w,h);

  // width and height ratio needed to resize all the tiles
  double rw = static_cast<double>(w)/m_board_w;
  double rh = static_cast<double>(h)/m_board_h;

  for(auto& [id,tile] :  m_table){
    m_log << "Rendering "<< tile.get_name() << std::endl;
    tile.render_region(m_window,m_resources,rw,rh,m_log);
    m_buttons.push_back(tile.make_button(m_window,m_resources,rw,rh));
  }

  for(auto [id,country] : m_countries)
    m_log << country << std::endl;

  for(auto [id,unit] : m_units)
    m_log << unit << std::endl;

  SDL_Rect box{0,0,static_cast<int>(w*0.25),static_cast<int>(h/30.)};
  Text back{m_font, "Back", SDL_Color{0,0,0,255},box,m_window,m_resources};
  std::cout << "test" << std::endl;
  m_exit_button = Button("Back",box,m_window,[this]()->void{this->close_game();},m_resources);
  m_window->present();
}

void Game::get_input(){
  m_log << "[Game: get_input()] Inside game input" << std::endl;
  while(SDL_WaitEvent(&m_event)){
    switch (m_event.type)
      {
      case SDL_MOUSEBUTTONDOWN:
        int x,y;
        SDL_GetMouseState(&x,&y);
        if(m_exit_button.pressed(x,y)){
          close_game();
          return ;
        }
        for(auto b : m_buttons){
          if(b.pressed(x,y)){
            b.action();
          }
        }
        return;
        break;
      case SDL_WINDOWEVENT:
        if (m_event.window.event == SDL_WINDOWEVENT_RESIZED){
          render_table();
          return;
        }else if(m_event.window.event == SDL_WINDOWEVENT_CLOSE){
         close_game();
         return;
        }
        break;
      default:
        break;
      }
  }
  return ;
};
