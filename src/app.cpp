#include <iostream>
#include <vector>
#include <format>
#include "app.hpp"
#include "color.hpp"
#include "SDL_video.h"
#include "button.hpp"
#include "text.hpp"
#include "sdl_wrap.hpp"
#include "log.hpp"
#include "resources_manager.hpp"
#include "SDL2/SDL.h"
#include "scenes.hpp"
#include "color.hpp"

constexpr char TITLE[] = "BETRAYAL";

void App::init() {
  SDL_WindowFlags flag = static_cast<SDL_WindowFlags>(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  init_SDL(flag);
  m_window->init("DIPLOMACY");
  m_font = TTF_OpenFont("./fonts/chailce-noggin-font/ChailceNogginRegular.ttf",16 );
  if(m_font==NULL){
    std::cerr << "Error: Font not loaded. Aborting"<< std::endl;
    LOGL("[App: init()] %s",TTF_GetError());
    exit(EXIT_FAILURE);
  }
  LOGL("[App: init()] sharing pointers with game");
  m_game.set_pointers(m_window,m_resources);
  m_next_scene = Scene_id::MAIN_MENU;
  dt.init();
}

void App::close(){
  m_running = false;
  LOGL("[App: close()] closing app");
  reset();
  LOGL("[App: close()] closing font");
  TTF_CloseFont(m_font);
  LOGL("[App: close()] closing window");
  m_window->close();
  LOGL("[App: close()] calling SDL_Quit()");
  SDL_Quit();
  m_scenes_stack.clear();
  m_next_scene = Scene_id::NONE;
  LOGL("[App: close()] scenes stack cleared");
}

void App::open(){
  m_running = true;
  /* running is set to false when App::close() is called. usually within a call of show_scene() */
  while(m_running){

    show_scene();
  }

}

void App::show_scene(){
  LOGL("[App: show_scene()] Current scene {}", scene2str(m_current_scene));
  LOGL("[App: show_scene()] Next scene {}", scene2str(m_next_scene));
  if (m_current_scene == m_next_scene)
    LOGL("[App: show_scene()] No need to update the rendering");
  else
    LOGL("[App: show_scene()] Rendering scene: {}", scene2str(m_next_scene));

  if(m_next_scene ==Scene_id::NONE){
    close();
    return;
  }
  m_current_scene = m_next_scene;

  LOGL(scene2str(m_current_scene));

  switch (m_current_scene)
    {
    case Scene_id::MAIN_MENU :
      main_menu();
      break;
    case Scene_id::NEW_GAME:
      new_game();
      break;
    case Scene_id::GAME:
      break;
    case Scene_id::NONE:
      LOGL("Closing game");
      close();
          return;
      break;
    default:
      break;
    }
  get_input();
}

void App::get_input(){
  LOGL("[App: get_input()] Getting input");
  while(SDL_WaitEvent(&m_event)){
    switch (m_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
      int x,y;
      SDL_GetMouseState(&x,&y);
      if(m_exit_button.pressed(x,y)){
        LOGL("[App: get_input()] exit button pressed");
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
      {
        return;
      } // show_scene();
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
  LOGL("[App: reset()] resetting window");
  m_buttons.clear();
  m_window->reset_rendering();
}

void App::main_menu(){
  render_main_menu();
  LOGL("[App: main_menu()] main menu renderered");
}

void App::render_main_menu(){
  LOGL("[App: render_main_menu] rendering main menu");
  reset();
  m_window->set_render_draw_color(get_color(Color::BACKGROUND));
  int w=0,h=0;
  m_window->get_window_center(w,h);
  
  // title 
  SDL_Rect Title_box{w/2,static_cast<int>(h*(0.25 - 1./14)),w,h/7};
  Text title{m_font,TITLE,get_color(Color::BLACK),Title_box,m_window,m_resources};
  /*
  // menu parameter/
       your games
        new game
        profile  // anchored to the middle:-> middle point is (w,h),
                 // so the top-left corner is (w - 0.5*box_width, h - 0.5 box_height)
       statistic
        settings
         close
  */

  float menu_box_w = w/2.0, menu_box_h=h/15.0;
  float menu_x = w - menu_box_w*0.5;
  float my_profile_y = h-0.5*menu_box_h;
  float h_off_set = 0.15*h;
  // my profile box  
  SDL_Rect temp_box{
    static_cast<int>(menu_x),
    static_cast<int>(my_profile_y),
    static_cast<int>(menu_box_w),
    static_cast<int>(menu_box_h)
  };
  Text my_profile{m_font,"My Profile",get_color(Color::BLACK),temp_box,m_window,m_resources};
  m_buttons.push_back(Button("My Profile",temp_box,m_window,
                             []()-> void {
                              LOGL("My Profile button pressed");
                              std::cout << "My Profile" << std::endl;
                             },m_resources));
  // new game
  temp_box.y = static_cast<int>(my_profile_y-h_off_set);
  Text new_game{m_font,"New Game",get_color(Color::BLACK),temp_box,m_window,m_resources};
  m_buttons.push_back(Button("New Game",temp_box,m_window,
                             [this]()->void {
                               LOGL("New game button pressed");
                               this->m_next_scene = Scene_id::NEW_GAME;
                               this->show_scene();
                             }
                             ,m_resources));
  // your Games
  temp_box.y = static_cast<int>(my_profile_y-2*h_off_set);
  Text your_game{m_font,"Your Games",get_color(Color::BLACK),temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Your Games",temp_box,m_window,
                             []()->void {
                               LOGL("Your Games button pressed");
                               std::cout << "Your Games" << std::endl;
                             },
                             m_resources));
  // statistic
  temp_box.y = static_cast<int>(my_profile_y+h_off_set);
  Text statistic{m_font,"Statistics",get_color(Color::BLACK),temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Statistics",temp_box,m_window,
                             []()->void {
                               LOGL("Statistics button pressed");
                               std::cout << "Statistics" << std::endl;
                             },m_resources));
  // settings
  temp_box.y = static_cast<int>(my_profile_y+2*h_off_set);
  Text setting{m_font,"Settings",get_color(Color::BLACK),temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Settings",temp_box,m_window,
                             []()->void {
                               LOGL("Settings button pressed");
                               std::cout << "Settings" << std::endl;
                             },m_resources));
  // close
  temp_box.y = static_cast<int>(my_profile_y+3*h_off_set);
  Text close{m_font,"Exit",get_color(Color::BLACK),temp_box,m_window,m_resources};
  m_exit_button= Button("Exit",temp_box,m_window,
                        [this]()->void {
                          LOGL("Exit button pressed");
                          this->m_next_scene = Scene_id::NONE;
                        },m_resources);
  m_window->present();
}   

void App::new_game(){
  render_new_game();
}

void App::render_new_game(){
  LOGL("[App: render_new_game] rendering new game screen");
  reset();
  m_window->set_render_draw_color(get_color(Color::BACKGROUND));
  int w,h;
  m_window->get_window_center(w,h);
  SDL_Rect Title_box{w/2,static_cast<int>(h*(0.25 - 1./14)),w,h/7};
  Text title{m_font,"New Game",get_color(Color::BLACK),Title_box,m_window,m_resources};
  float menu_box_w = w/2.0, menu_box_h=h/15.0;
  float menu_x = w - menu_box_w*0.5;
  float menu_y = h-0.5*menu_box_h;
  float h_off_set = 0.15*h;
  // Centered box
  SDL_Rect box{
    static_cast<int>(menu_x),
    static_cast<int>(menu_y),
    static_cast<int>(menu_box_w),
    static_cast<int>(menu_box_h)
  };
  Text game{m_font,"Ancient Mediterrean",get_color(Color::BLACK),box,m_window,m_resources};
  m_buttons.push_back(Button("Ancient Mediterrean",box,m_window,
                             [this]()->void {
                               LOGL("Starting Ancient Mediterrean game");
                               this-> start_game(Game_map::ANCIENT_MEDITERREAN);
                             },m_resources));

  box.y = static_cast<int>(menu_y + h_off_set) ;
  Text back{m_font, "Back", get_color(Color::BLACK),box,m_window,m_resources};
  m_exit_button = Button("Back",box,m_window,
                         [this]()->void {
                           LOGL("Back button pressed");
                           this-> m_next_scene=Scene_id::MAIN_MENU;
                         },m_resources);
  m_window->present();
}

void App::start_game(Game_map game){
  LOGL("[App: start_game()] starting game");
  m_game.start(game);
  LOGL("[App: start_game()] game ended");
  m_next_scene = Scene_id::NEW_GAME;
}
