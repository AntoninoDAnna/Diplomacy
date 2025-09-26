#include "game.hpp"
#include "region.hpp"
#include "country.hpp"
#include "manager.hpp"
#include "log.hpp"
#include "utilities.hpp"
#include "unit.hpp"
#include "globals.hpp"
#include "button.hpp"
#include "text.hpp"
#include "window.hpp"
//#include "SDL2/SDL_ttf.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
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
  void reset(){m_seed = 1;};
  private:
  ID m_seed = 1;
};

static ID_gen g_id = ID_gen();

Game::Game() {}

void Game::set_window(std::shared_ptr<Core::Window> &w) { m_window = w; }

void Game::set_manager(std::shared_ptr<Core::Manager>& r){
  m_resources = r;
}

void Game::set_buttons_vector(std::vector<Core::Button> *v) { m_buttons = v; }

void Game::set_exit_button(Core::Button *exit) { m_exit_button = exit; }

Game::~Game(){}

void Game::start(Game_map& game){
  LOGL("[Game: start_game()] starting game");
  switch(game){
    case Game_map::ANCIENT_MEDITERREAN:
      m_gamename = g_AM;
      break;
    default:
      std::cerr<<"Game error: Undefined game map"<<std::endl;
      LOGL("Game error: Undefined game map");
      exit(1);
      break;
  }
  LOGL("[Game: start_game()] game: %s ", m_gamename);
  LOGL("[Game: start_game()] updatig g_TILES file in m_resources");
  m_resources->replace_file(g_TILES,img_folder/m_gamename/tiles_file);
  LOGL("[Game: start_game()] updatig g_MAP file in m_resources");
  m_resources->replace_file(g_MAP,img_folder/m_gamename/(m_gamename+".png"));
  LOGL("[Game: start_game()] updatig g_MAP texture in m_resources");
  m_resources->replace_texture(g_MAP,m_resources->get_file(g_MAP),m_window);
  read_map(m_resources->get_file(m_gamename));
  //render_table();
  m_running = true;
}

ID Game::get_region_ID(const std::string& abb){
  LOGL("[Game: get_region_ID()] searcing for region %s",abb);
  for(auto& [ID,R] : m_table){
    if(R.get_abbreviation().compare(abb)==0)
      return ID;
  }
  LOGL("[Game: get_region_ID()] search failed");
  exit(1);
}

void Game::read_map(const std::filesystem::path& filename){
  LOGL("[Game: read_map()] reading map in path %s", filename.string());
  std::ifstream file(filename,std::ios::in);
  int n_tile;
  file >> n_tile;  
  Util::next_line(file,2);  
  std::string file_line;
  std::vector<std::string> fields_name;
  ID id;
  uint32_t flag=0x0;
  // fill the table
  for(int i=0; i<n_tile; i++){
    std::getline(file,file_line); 
    // name abbreviation sc land sea   
    fields_name = Util::split_line(file_line);
    id = g_id();
    if (std::stoi(fields_name[2]))
      flag |= Region_Flags::SC;
    if (std::stoi(fields_name[3]))
      flag |= Region_Flags::LAND;
    if (std::stoi(fields_name[4]))
      flag |= Region_Flags::SEA;

    m_table.emplace(id,Region(fields_name[0],fields_name[1],flag,id));

    m_resources->add_file(fields_name[1],img_folder/m_gamename/tiles_folder/(fields_name[0]+".png"));
  }
  LOGL("[Game: read_map()] All Regions read");
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
  LOGL("[Game: read_map()] All neighbors set");
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
  LOGL("[Game: read_map()] All Countries set");

  file.close();
  file.open(m_resources->get_file(g_TILES),std::ios::in);
  Util::next_line(file);
  int x,y,w,h;
  file >> x >> x >> m_board_w >> m_board_h;
  std::string abb;

  while(!file.eof()){
    file >> abb >> x >> y >> w >> h;
    id = get_region_ID(abb);
    m_table.at(id).set_region_on_map(x,y,w,h,m_window,m_resources);
  }
  file.close();
  return;
}

void Game::close_game(){
  m_running = false;
  LOGL("[Game: close_game] closing game");
  m_table.clear();
  LOGL("[Game: close_game] table cleared");
  m_countries.clear();
  LOGL("[Game: close_game] countries cleared");
  m_units.clear();
  LOGL("[Game: close_game] units cleared");
  g_id.reset();
};

void Game::render_table(){
  LOGL("[Game: render_table] rendering table");
  LOGL("[Game: render_table] clearing buttons");
  m_buttons->clear();
  LOGL("[Game: render_table] resetting rendering");
  m_window->reset_rendering();
  LOGL("[Game: render_table] rendering map");
  m_window->render_copy(m_resources->get_texture(g_MAP),NULL,NULL);

  int w,h;
  m_window->get_renderer_size(w,h);

  // width and height ratio needed to resize all the tiles
  double rw = static_cast<double>(w)/m_board_w;
  double rh = static_cast<double>(h)/m_board_h;

  for(auto& [id,tile] :  m_table){
    LOGL("Rendering %s", tile.get_name());
    if(tile.is_rendered()){
      tile.render_region(m_window,m_resources,rw,rh);
      m_buttons->push_back(tile.make_button(m_window, m_resources, rw, rh));
    }
  }

  for(auto [id,country] : m_countries) LOGL(country.string());

  //for(auto [id,unit] : m_units) LOGL(unit);

  SDL_Rect box{0,0,static_cast<int>(w*0.25),static_cast<int>(h/30.)};
  Core::Text back{m_font, "Back", SDL_Color{0,0,0,255},box,m_window,m_resources};
  *m_exit_button = Core::Button("Back",box,m_window,[this]()->void{this->close_game();},m_resources);
}
