#include "../include/game.h"
#include "../include/region.h"
#include "../include/country.h"
#include "../include/resources_manager.h"
#include "../include/log.h"
#include "../include/utilities.h"
#include "../include/unit.h"
#include "../include/globals.h"
#include "../include/button.h"
#include "../include/text.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <vector>
#include <iomanip>
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
  if(!m_LOG.is_open()){
    std::cerr << "cannot_open log file. ABORTING"<<std::endl;
    exit(EXIT_FAILURE);
  }
  m_log << "Openning game log"<<std::endl;
}

Game::~Game(){
  m_log << "closing for destruction of Game instance"<<std::endl;
  m_log.close();
}

void Game::start_game(Game_map game){
  
  switch(game){
    case Game_map::ANCIENT_MEDITERREAN:
      m_gamename = g_AM;
      break;
    default:
      LOG<<"Error: Undefined game map"<<std::endl;
      exit(1);
      break;
  }
  m_resources->replace_file(g_TILES,img_folder/m_gamename/tiles_file);
  m_resources->replace_file(g_MAP,img_folder/m_gamename/(m_gamename+".png"));
  m_resources->replace_texture(g_MAP,m_resources->get_file(g_MAP),m_r);
  read_map(m_resources->get_file(m_gamename));

}

void Game::read_map(std::filesystem::path filename){
  std::ifstream file(filename,std::ios::in);
  int n_tile;
  file >> n_tile;  
  Util::next_line(file,2);  
  std::string file_line;
  std::vector<std::string> fields_name;
  bool sc,land,sea;
  ID id;
  std::unordered_map<std::string, ID> abb_to_ID;
  // fill the table
  LOG << std::boolalpha;
  for(int i=0; i<n_tile; i++){
    std::getline(file,file_line); 
    // name abbreviation sc land sea   
    fields_name = Util::split_line(file_line);
    id = g_id();
    sc = std::stoi(fields_name[2]);
    land = std::stoi(fields_name[3]);
    sea  = std::stoi(fields_name[4]);
    m_table.emplace(id,Region(fields_name[0],fields_name[1],sc,land,sea,id));
    abb_to_ID.emplace(fields_name[1],id);
    m_resources->add_file(fields_name[1],img_folder/m_gamename/tiles_folder/(fields_name[0]+".png"));
  }
  // read the neigbhors.
  Util::next_line(file);
  std::list<ID> neighbors;
  for(int i=0; i<n_tile; i++){
    std::getline(file, file_line);
    fields_name = Util::split_line(file_line);
    Region* current_R = &m_table.at(abb_to_ID.at(fields_name[0]));
    for(size_t i=1; i<fields_name.size(); i++){
      neighbors.push_back(abb_to_ID.at(fields_name[i]));
    }
    current_R->set_neighbors(neighbors);
    neighbors.clear();
  }
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
      id_r = abb_to_ID.at(fields_name[i]);
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
  
  file.close();
  
  file.open(m_resources->get_file(g_TILES),std::ios::in);
  
  std::string abb;
  
  int x,y,w,h;
  
  while(!file.eof()){
    file >> abb >> x >> y >> w >> h;
    id = abb_to_ID.at(abb);
    m_table.at(id).set_region_on_map(x,y,w,h,m_r,m_resources);
  }
  file.close();
  return;
}

void Game::close_game(){
  m_table.clear();
  m_countries.clear();
  m_units.clear();
  m_LOG<< "closing game" << std::endl;
  m_LOG.close();
};

void Game::render_table(){
  LOG << "rendering table"<<std::endl;
  m_buttons.clear();
  if(SDL_RenderClear(m_r)<0) LOG << SDL_GetError() << std::endl;
  SDL_Texture *map = m_resources->get_texture(g_MAP);
  int win_w,win_h;
  SDL_GetRendererOutputSize(m_r,&win_w,&win_h);
  if(SDL_RenderCopy(m_r,map,NULL,NULL)<0)
    LOG << SDL_GetError() << std::endl;
  SDL_RenderPresent(m_r);
  for(auto [id,tile] :  m_table){
    m_LOG << tile << std::endl;
    // tile.render_region(m_r);
    // m_buttons.push_back(tile.make_button(m_r));
  }

  for(auto [id,country] : m_countries)
    m_LOG << country << std::endl;

  for(auto [id,unit] : m_units)
    m_LOG << unit << std::endl;
  
  SDL_Rect box{100,100,0,0};
  Text back{m_font, "BACK", SDL_Color{0,0,0,255},box,m_r,m_resources};
  m_exit_button = Button("BACK",box,m_r,[this]()->void {this->close_game();},m_resources);  
  SDL_RenderPresent(m_r);
  get_input();
}

void Game::get_input(){
  while(SDL_WaitEvent(&m_event)){
    LOG << "inside game input" << std::endl;      
    switch (m_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
      int x,y;
      SDL_GetMouseState(&x,&y);
      if(m_exit_button.pressed(x,y)){
        m_exit_button.action();
        return;
      } 
      for(auto b : m_buttons)
        if(b.pressed(x,y)) b.action(); 
      render_table();  
      break;
    case SDL_WINDOWEVENT:
      if (m_event.window.event == SDL_WINDOWEVENT_RESIZED)  
        render_table();
      break;
    case SDL_QUIT:
      SDL_Quit();
      break;
    default:
      break;
    }
  }
}