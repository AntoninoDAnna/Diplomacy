#include "../include/game.h"
#include "../include/region.h"
#include "../include/country.h"
#include "../include/file_manager.h"
#include "../include/texture_manager.h"
#include "../include/log.h"
#include "../include/utilities.h"
#include "../include/unit.h"
#include "../include/globals.h"
#include "../include/button.h"
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

Game::~Game(){
  if(m_LOG.is_open()){
    m_LOG<< "closing for destruction of Game instance"<<std::endl;
    m_LOG.close();
  }
}
void Game::start_game(Game_map game){
  m_LOG.open("../bin/log/logfile.log",std::fstream::out);
  if(!m_LOG.is_open()){
    std::cout << "cannot_open log file"<<std::endl;
    exit(1);
  }
  switch(game){
    case Game_map::ANCIENT_MEDITERREAN:
      m_gamename = g_AM;
      break;
    default:
      LOG<<"Error: Undefined game map"<<std::endl;
      exit(1);
      break;
  }
  g_FILES.replace(g_TILES,img_folder/m_gamename/tiles_file);
  g_FILES.replace(g_MAP,img_folder/m_gamename/(m_gamename+".png"));
  g_TEXTURE.replace(g_MAP,g_FILES.get(g_MAP),m_r);
  read_map(g_FILES.get(m_gamename));
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
    if(!(sea && !land))
      g_FILES.add(fields_name[1],img_folder/m_gamename/tiles_folder/(fields_name[0]+".png"));
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
  file.open(g_FILES.get(g_TILES),std::ios::in);
  std::string abb;
  int x,y;
  while(!file.eof()){
    file >> abb >> x >> y;
    id = abb_to_ID.at(abb);
    m_table.at(id).set_vertex(x,y);
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
  if(SDL_RenderClear(m_r)<0) LOG << SDL_GetError() << std::endl;
  SDL_Texture *map = g_TEXTURE.get(g_MAP);
  int win_w,win_h;
  SDL_GetRendererOutputSize(m_r,&win_w,&win_h);
  if(SDL_RenderCopy(m_r,map,NULL,NULL)<0)
    LOG << SDL_GetError() << std::endl;
  SDL_RenderPresent(m_r);
  for(auto [id,tile] :  m_table)
    m_LOG << tile << std::endl;

  for(auto [id,country] :  m_countries)
    m_LOG << country << std::endl;

  for(auto [id,unit] : m_units)
    m_LOG << unit << std::endl;

}