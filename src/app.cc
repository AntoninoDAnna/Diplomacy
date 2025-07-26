#include <iostream>
#include <vector>
#include <memory>
#include "../include/app.h"
#include "../include/button.h"
#include "../include/text.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "../include/log.h"
#include "../include/resources_manager.h"

constexpr SDL_Color BACKGROUND{54,220,215,255};
constexpr SDL_Color MENU_COLOR{54,121,220,255};
constexpr SDL_Color WHITE{255,255,255,255};
constexpr SDL_Color BLACK{0,0,0,255};
constexpr char TITLE[] = "BETRAYAL"; 
int g_cshow = 0;
int g_cgetinput = 0;

void App::init(){
  m_log.open("../bin/log/logfile.log",std::ios_base::out);
  if(!m_log.is_open()){
    std::cerr << "cannot open app log file. ABORTING"<<std::endl;
    exit(EXIT_FAILURE);
  }
  m_log << "[App: start()] Opening log file"<< std::endl;
  if(SDL_Init(SDL_INIT_VIDEO) <0) {
    std::cerr <<"Error in initiating SDL, aborting" << std::endl;
    m_log << "[App: start()]" << SDL_GetError()<< std::endl;
    exit(EXIT_FAILURE);
  }
  if(TTF_Init() == -1){
    std::cerr << "Error in initializing TTF, aborting"<< std::endl;
    m_log << "[App: start()]" << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  };
  if(IMG_Init(IMG_INIT_PNG) ==0){
    std::cerr << "Error in initializing PNG, aborting"<< std::endl;
    m_log << "[App: start()]" << IMG_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  m_window->init();
  m_font = TTF_OpenFont("./fonts/chailce-noggin-font/ChailceNogginRegular.ttf",16 );
  if(m_font==NULL){
    std::cerr << "Error: Font not loaded. Aborting"<< std::endl;
    m_log << "[App: start()]"<< TTF_GetError()<< std::endl;
    exit(EXIT_FAILURE);
  }
  m_next_scene = Scene_id::MAIN_MENU;
}

void App::close(){
  m_running = false;
  m_log << "[App: close()] closing app" << std::endl;
  reset();
  m_log << "[App: close()] closing font" << std::endl;
  TTF_CloseFont(m_font);
  m_log << "[App: close()] closing window" << std::endl;
  m_window->close(m_log);
  m_log << "[App: close()] calling SDL_Quit()" <<std::endl;
  SDL_Quit();
  m_scenes_stack.clear();
  m_next_scene = Scene_id::NONE;
  m_log << "[App: close()] scenes stack cleared" << std::endl;
  std::cout << "g_cshow     = " << g_cshow << std::endl;
  std::cout << "g_cgetinput = " << g_cgetinput << std::endl;
  if(m_log.is_open()){
    m_log << "[App: close()] Closing log file"<< std::endl;
    //m_log.close();
  }
  std::cout << "log file closed" << std::endl;
}

void App::open(){
  m_running = true;
  /* running is set to false when App::close() is called. usually within a call of show_scene() */
  while(m_running){
    show_scene();
  }

}

void App::show_scene(){
  g_cshow++;
  m_log << "[App: show_scene()] Current scene" << m_current_scene<< std::endl;
  m_log << "[App: show_scene()] Next scene   " << m_next_scene << std::endl;
  if (m_current_scene == m_next_scene)
    m_log << "[App: show_scene()] No need to update the rendering"<< std::endl;
  else
    m_log << "[App: show_scene()] Rendering scene: " << m_next_scene << std::endl;
  if(m_next_scene ==Scene_id::NONE){
    close();
    g_cshow--;
    return;
  }
  if(m_next_scene != m_current_scene){
    m_current_scene = m_next_scene;
    switch (m_current_scene)
      {
      case Scene_id::MAIN_MENU :
        m_log << "MAIN_MENU" << std::endl;
        main_menu();
        break;
      case Scene_id::NEW_GAME:
        m_log << "NEW_GAME" << std::endl;
        new_game();
        break;
      case Scene_id::GAME:
        m_log << "GAME" << std::endl;
        render_game();
        break;
      case Scene_id::NONE:
        m_log << "Closing game" << std::endl;
        close();
        g_cshow--;
        return;
        break;
      default:
        break;
      }
  }
  get_input();
  g_cgetinput--;
  g_cshow--;
}

void App::get_input(){
  g_cgetinput++;
  m_log << "[App: get_input()] Getting input" << std::endl;
  while(SDL_WaitEvent(&m_event)){
    switch (m_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
      int x,y;
      SDL_GetMouseState(&x,&y);
      if(m_exit_button.pressed(x,y)){
        m_log << "[App: get_input()] exit button pressed"<< std::endl;
        m_exit_button.action();
        return;
      }
      for(auto b : m_buttons){
        if(b.pressed(x,y)){
          b.action();
          return;
        }
      }
      break;
    case SDL_WINDOWEVENT:
      if (m_event.window.event == SDL_WINDOWEVENT_RESIZED)
      {} // show_scene();
      else if(m_event.window.event ==SDL_WINDOWEVENT_CLOSE){
        close();
        return;
      }
      break;
    default:
      break;
    }
  }
}


void App::reset(){
  m_log << "[App: reset()] resetting window"<< std::endl;
  m_buttons.clear();
  m_window->reset_rendering();
}

void App::main_menu(){
  render_main_menu();
  m_log << "[App: main_menu()] main menu renderered"<<  std::endl;
}

void App::render_main_menu(){
  m_log << "[App: render_main_menu] rendering main menu" << std::endl;
  reset();
  m_window->set_render_draw_color(BACKGROUND);

  int w,h;
  m_window->get_window_center(w,h);

  // title 
  SDL_Rect Title_box{w/4,static_cast<int>(h*(1./5 - 1./14)),w/2,h/7};
  Text title{m_font,TITLE,BLACK,Title_box,m_window,m_resources};
  // menu parameters
  // 
  // your games
  // new game
  // profile <-- this is anchored to the center of the screen
  // statistic
  // settings
  // close

  int menu_box_w = w/4,menu_box_h=h/30,menu_x = static_cast<int>(w*(0.5-0.125));
  float my_profile_y = h*(1./2-1./20); 

  // my profile box  
  SDL_Rect temp_box{menu_x,static_cast<int>(my_profile_y),menu_box_w,menu_box_h};
  Text my_profile{m_font,"My Profile",BLACK,temp_box,m_window,m_resources};
  m_buttons.push_back(Button("My Profile",temp_box,m_window,
                             [this]()-> void {
                               this->m_log << "My Profile button pressed"<< std::endl;
                               std::cout << "My Profile" << std::endl;
                             },m_resources));
  // new game
  temp_box.y = static_cast<int>(my_profile_y-h*(0.06));
  Text new_game{m_font,"New Game",BLACK,temp_box,m_window,m_resources};
  m_buttons.push_back(Button("New Game",temp_box,m_window,
                             [this]()->void {
                               this-> m_log << "New game button pressed"<< std::endl;
                               this->m_next_scene = Scene_id::NEW_GAME;
                               this->show_scene();
                             }
                             ,m_resources));

  // your Games
  temp_box.y = static_cast<int>(my_profile_y-h*(0.12));
  Text your_game{m_font,"Your Games",BLACK,temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Your Games",temp_box,m_window,
                             [this]()->void {
                               this->m_log << "Your Games button pressed"<< std::endl;
                               std::cout << "Your Games" << std::endl;
                             },
                             m_resources));
  // statistic
  temp_box.y = static_cast<int>(my_profile_y+h*(0.06));
  Text statistic{m_font,"Statistics",BLACK,temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Statistics",temp_box,m_window,
                             [this]()->void {
                               this->m_log << "Statistics button pressed"<< std::endl;
                               std::cout << "Statistics" << std::endl;
                             },m_resources));
  // settings
  temp_box.y = static_cast<int>(my_profile_y+h*(0.12));
  Text setting{m_font,"Settings",BLACK,temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Settings",temp_box,m_window,
                             [this]()->void {
                               this-> m_log << "Settings button pressed"<< std::endl;
                               std::cout << "Settings" << std::endl;
                             },m_resources));
  // close
  temp_box.y = static_cast<int>(my_profile_y+h*(0.18));
  Text close{m_font,"Exit",BLACK,temp_box,m_window,m_resources};
  m_exit_button= Button("Exit",temp_box,m_window,
                        [this]()->void {
                          this->m_log << "Exit button pressed" << std::endl;
                          this->m_next_scene = Scene_id::NONE;
                        },m_resources);
  m_window->present();
}   

void App::new_game(){
  render_new_game();
}

void App::render_new_game(){
  m_log << "[App: render_new_game] rendering new game screen"<<std::endl;
  reset();
  m_window->set_render_draw_color(BACKGROUND);
  int w,h;
  m_window->get_window_center(w,h);
  SDL_Rect box{w/2-100,h/2-50,200,100};
  Text game{m_font,"Ancient Mediterrean",BLACK,box,m_window,m_resources};
  m_buttons.push_back(Button("Ancient Mediterrean",box,m_window,
                             [this]()->void {
                               this-> m_log << "Starting Ancient Mediterrean game"<< std::endl;
                               this-> start_game(Game_map::ANCIENT_MEDITERREAN);
                             },m_resources));
  box.x=0;
  box.y=0;
  Text back{m_font, "BACK", BLACK,box,m_window,m_resources};
  m_exit_button = Button("BACK",box,m_window,
                         [this]()->void {
                           this->m_log << "Back button pressed"<< std::endl;
                           this-> m_next_scene=Scene_id::MAIN_MENU;
                         },m_resources);
  m_window->present();
}

void App::start_game(Game_map game){
  m_log << "[App: start_game()] starting game"<< std::endl;
  m_game.start_game(game,m_window,m_resources);
  render_game();
  m_scenes_stack.pop_back();
  show_scene();
}

void App::render_game(){
  m_log << "[App: render_game()] rendering game: "<<std::endl;
  reset();
  m_game.render_table();
  while(m_game.get_input()) {
      // game plying ?
    }
}
