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



App::App(){  
  m_log.open("../bin/log/logfile.log",std::ios_base::out);
  if(!m_log.is_open()){
    std::cerr << "cannot open app log file. ABORTING"<<std::endl;
    exit(EXIT_FAILURE);
  }
  m_log << "[App] Opening log file"<< std::endl;

  if(SDL_Init(SDL_INIT_VIDEO) <0) {
    std::cerr <<"Error in initiating SDL, aborting" << std::endl;
    m_log << "[App]" << SDL_GetError()<< std::endl;
    exit(EXIT_FAILURE);
  }

  if(TTF_Init() == -1){
    std::cerr << "Error in initializing TTF, aborting"<< std::endl;
    m_log << "[App]" << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  };

  if(IMG_Init(IMG_INIT_PNG) ==0){
    std::cerr << "Error in initializing PNG, aborting"<< std::endl;
    m_log << "[App]" << IMG_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  m_window->init();
  m_font = TTF_OpenFont("./fonts/chailce-noggin-font/ChailceNogginRegular.ttf",16 );
  if(m_font==NULL){
    std::cerr << "Error: Font not loaded. Aborting"<< std::endl;
    m_log << "[App]"<< TTF_GetError()<< std::endl;
    exit(EXIT_FAILURE);
  }


  //share pointers with Game
  m_game.set_font(m_font);

  show(Scene_id::MAIN_MENU);
}

App::~App(){
  m_log << "[App] destroying app" << std::endl;
  reset();
  m_log << "[App: ~App()] closing font" << std::endl;
  TTF_CloseFont(m_font);
  m_log << "[App: ~App()] closing window" << std::endl;
  m_window->close(m_log);
  m_log << "[App: ~App()] calling SDL_Quit()" <<std::endl;
  SDL_Quit();
  if(m_log.is_open()){
    m_log << "[App: ~App()] Closing log file"<< std::endl;
    m_log.close();
  }
  std::cout << "log file closed" << std::endl;
}

void App::show(Scene_id scene_id){
  if(m_scenes.back()!=scene_id) 
    m_scenes.push_back(scene_id);

  m_log << "[App] Showing scene: ";
  switch (scene_id)
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
  default:
    break;
  }
}

void App::get_input(){
  m_log << "[App] Getting input" << std::endl;
  while(SDL_WaitEvent(&m_event)){
    switch (m_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
      int x,y;
      SDL_GetMouseState(&x,&y);
      if(m_exit_button.pressed(x,y)){
        m_log << "[App: get_input()] exit button pressed"<< std::endl;
        m_exit_button.action();
        m_scenes.pop_back();
        return;
      } 
      for(auto b : m_buttons)
        if(b.pressed(x,y)) b.action(); 
      show(m_scenes.back());  
      break;
    case SDL_WINDOWEVENT:
      if (m_event.window.event == SDL_WINDOWEVENT_RESIZED)  
        show(m_scenes.back());
      break;
    case SDL_QUIT:
      SDL_Quit();
      break;
    default:
      break;
    }
  }
}


void App::reset(){
  m_log << "[App] resetting window"<< std::endl;
  m_buttons.clear();
  m_window->reset_rendering();
}

void App::main_menu(){
  render_main_menu();
  get_input();
}

void App::render_main_menu(){
  m_log << "[App] rendering main menu" << std::endl;
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
  m_buttons.push_back(Button("My Profile",temp_box,m_window,[]()-> void {std::cout << "my Profile"<< std::endl;},m_resources));
  // new game
  temp_box.y = static_cast<int>(my_profile_y-h*(0.06));
  Text new_game{m_font,"New Game",BLACK,temp_box,m_window,m_resources};
  m_buttons.push_back(Button("New Game",temp_box,m_window, [this]()->void {this->show(Scene_id::NEW_GAME);},m_resources));

  // your Games
  temp_box.y = static_cast<int>(my_profile_y-h*(0.12));
  Text your_game{m_font,"Your Games",BLACK,temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Your Games",temp_box,m_window,[]()->void {std::cout << "Your Game" << std::endl;},m_resources));

  // statistic
  temp_box.y = static_cast<int>(my_profile_y+h*(0.06));
  Text statistic{m_font,"Statistic",BLACK,temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Statistic",temp_box,m_window,[]()->void {std::cout << "Statistic" << std::endl;},m_resources));

  // settings
  temp_box.y = static_cast<int>(my_profile_y+h*(0.12));
  Text setting{m_font,"Settings",BLACK,temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Settings",temp_box,m_window,[]()->void {std::cout << "Setting" << std::endl;},m_resources));

  // close
  temp_box.y = static_cast<int>(my_profile_y+h*(0.18));
  Text close{m_font,"Exit",BLACK,temp_box,m_window,m_resources};
  m_exit_button= Button("Exit",temp_box,m_window,[]()->void {SDL_Quit() ;},m_resources);
  m_window->present();
}   

void App::new_game(){
  render_new_game();
  get_input();
}

void App::render_new_game(){
  m_log << "[App] rendering new game screen"<<std::endl;
  reset();
  m_window->set_render_draw_color(BACKGROUND);
  int w,h;
  m_window->get_window_center(w,h);
  SDL_Rect box{w/2-100,h/2-50,200,100};
  Text game{m_font,"Ancient Mediterrean",BLACK,box,m_window,m_resources};
  m_buttons.push_back(Button("Ancient Mediterrean",box,m_window,[this]()->void {this->start_game(Game_map::ANCIENT_MEDITERREAN);},m_resources));
  box.x=0;
  box.y=0;
  Text back{m_font, "BACK", BLACK,box,m_window,m_resources};
  m_exit_button = Button("BACK",box,m_window,[this]()->void {m_game.close_game();},m_resources);
  m_window->present();
}

void App::start_game(Game_map game){
  m_log << "[App] starting game"<< std::endl;
  m_scenes.push_back(Scene_id::GAME);
  m_game.start_game(game,m_window,m_resources);
  render_game();
}

void App::render_game(){
  m_log << "[App] rendering game: "<<std::endl;
  reset();
  m_game.render_table();
  show(Scene_id::MAIN_MENU);
}
