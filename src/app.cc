#include <iostream>
#include <vector>
#include <memory>
#include "../include/app.h"
#include "../include/button.h"
#include "../include/text.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "../include/log.h"

constexpr SDL_Color BACKGROUND{54,220,215,255};
constexpr SDL_Color MENU_COLOR{54,121,220,255};
constexpr SDL_Color WHITE{255,255,255,255};
constexpr SDL_Color BLACK{0,0,0,255};
constexpr char TITLE[] = "BETRAYAL"; 

App::App(){  
  if(SDL_Init(SDL_INIT_VIDEO) <0) {
    std::cerr <<"Error in initiating SDL, aborting" << std::endl;
    std::cout << SDL_GetError()<< std::endl;
    exit(1);
  }
  if(TTF_Init() == -1){
    std::cerr << "Error in initiationg TTF, aborting"<< std::endl;
    std::cout << TTF_GetError() << std::endl;
    exit(1);
  };
  if(IMG_Init(IMG_INIT_PNG) ==0){
    std::cerr << "Error in initiationg TTF, aborting"<< std::endl;
    std::cout << IMG_GetError() << std::endl;
    exit(1);
  }

  // SDL_CreateWindowAndRenderer(WIDTH*SCALE,HEIGHT*SCALE,0,&window,&renderer);
  m_window = SDL_CreateWindow("Diplomacy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,m_WIDTH*m_SCALE,m_HEIGHT*m_SCALE,SDL_WINDOW_RESIZABLE);
  if(m_window==NULL){
    std::cerr << SDL_GetError() << std::endl;  
    exit(1);
  }
  m_renderer =SDL_CreateRenderer(m_window,1,0);
  if(m_renderer==NULL){
    std::cerr << SDL_GetError() << std::endl;  
    exit(1);
  }
  m_font = TTF_OpenFont("./fonts/chailce-noggin-font/ChailceNogginRegular.ttf",16 );
  if(m_font==NULL){
    std::cout << "Error: Font not loaded"<< std::endl;
    std::cout << TTF_GetError()<< std::endl;
    exit(1);
  }

  SDL_RenderSetScale(m_renderer,m_SCALE,m_SCALE);
  
  show(Scene_id::MAIN_MENU);
  get_input();
}

App::~App(){
  reset_rendering();
  SDL_DestroyWindow(m_window);
  TTF_CloseFont(m_font);
  SDL_DestroyRenderer(m_renderer);
  SDL_Quit();
}

void App::show(Scene_id scene_id){
  m_current_scene = scene_id;
  switch (scene_id)
  {
  case Scene_id::MAIN_MENU :
    render_main_menu();
    break;
  case Scene_id::NEW_GAME:
    std::cout << "New game rendering"<< std::endl;
    break;
  default:
    break;
  }
}

void App::get_input(){
  while(SDL_WaitEvent(&m_event)){
    switch (m_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
      int x,y;
      SDL_GetMouseState(&x,&y);
      for(auto b : m_buttons)
        if(b.pressed(x,y)) b.action();   
      break;
    case SDL_WINDOWEVENT:
      if (m_event.window.event == SDL_WINDOWEVENT_RESIZED)  
        show(m_current_scene);
      break;
    case SDL_QUIT:
      SDL_Quit();
      break;
    default:
      break;
    }
  }
}

void App::get_window_center(int& x, int& y){
  int w,h;
  SDL_GetWindowSize(m_window,&w,&h);
  x = w/(2*m_SCALE);
  y = h/(2*m_SCALE);
}


void App::reset_rendering(){
  m_buttons.clear();
  // SDL_RenderClear(m_renderer);
}

void App::render_main_menu(){
  LOG("rendering main menu");
  reset_rendering();  
  SDL_SetRenderDrawColor(m_renderer,BACKGROUND.r,BACKGROUND.b,BACKGROUND.g,BACKGROUND.a);
  SDL_RenderClear(m_renderer);

  int w,h;
  SDL_GetWindowSize(m_window,&w,&h);

  // title 
  SDL_Rect Title_box{w/4,static_cast<int>(h*(1./5 - 1./14)),w/2,h/7};
  Text title{m_font,TITLE,BLACK,Title_box,m_renderer};
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
  Text my_profile{m_font,"My Profile",BLACK,temp_box,m_renderer};
  m_buttons.push_back(Button("My Profile",temp_box,m_renderer,[]()-> void {std::cout << "my Profile"<< std::endl;}));
  // new game
  temp_box.y = static_cast<int>(my_profile_y-h*(0.06));
  Text new_game{m_font,"New Game",BLACK,temp_box,m_renderer};
  m_buttons.push_back(Button("New Game",temp_box,m_renderer, [this]()->void {this->show(Scene_id::NEW_GAME);}));

  // your Games
  temp_box.y = static_cast<int>(my_profile_y-h*(0.12));
  Text your_game{m_font,"Your Games",BLACK,temp_box,m_renderer};
  m_buttons.push_back(Button("Your Games",temp_box,m_renderer,[]()->void {std::cout << "Your Game" << std::endl;}));

  // statistic
  temp_box.y = static_cast<int>(my_profile_y+h*(0.06));
  Text statistic{m_font,"Statistic",BLACK,temp_box,m_renderer};
  m_buttons.push_back(Button("Statistic",temp_box,m_renderer,[]()->void {std::cout << "Statistic" << std::endl;}));

  // settings
  temp_box.y = static_cast<int>(my_profile_y+h*(0.12));
  Text setting{m_font,"Settings",BLACK,temp_box,m_renderer};
   m_buttons.push_back(Button("Settings",temp_box,m_renderer,[]()->void {std::cout << "Setting" << std::endl;}));

  // close
  temp_box.y = static_cast<int>(my_profile_y+h*(0.18));
  Text close{m_font,"Exit",BLACK,temp_box,m_renderer};
  m_buttons.push_back(Button("Exit",temp_box,m_renderer,SDL_Quit));
  SDL_RenderPresent(m_renderer);
  
  return;
}   

// void App::render_new_game(){
//   reset_rendering();
//   SDL_SetRenderDrawColor(m_renderer,BACKGROUND.r,BACKGROUND.b,BACKGROUND.g,BACKGROUND.a);
//   int w,h;
//   SDL_GetWindowSize(m_window,&w,&h);

//   SDL_RenderPresent(m_renderer);
//   return;
// }
