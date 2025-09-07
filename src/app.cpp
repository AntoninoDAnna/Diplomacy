#include <iostream>
#include <vector>
#include "app.hpp"
#include "color.hpp"
#include "button.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "text.hpp"
#include "sdl_wrap.hpp"
#include "log.hpp"
#include "SDL2/SDL.h"
#include "scenes.hpp"
#include "color.hpp"
#include "window.hpp"

constexpr char TITLE[] = "BETRAYAL";

void App::init() {
  LOGL("Initializing App");
  init_SDL(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  LOGL("Initiliazing openGL3");
  m_window->init("DIPLOMACY",
                 static_cast<SDL_WindowFlags>( SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED));
  m_font = TTF_OpenFont("./fonts/chailce-noggin-font/ChailceNogginRegular.ttf",16 );
  if(m_font==NULL){
    LOGL("Error: Font not loaded: {}",TTF_GetError());
    exit(EXIT_FAILURE);
  }
  LOGL("Sharing pointers with game");
  m_game.set_pointers(m_window,m_resources);
  dt.set_window(m_window);
  dt.init();
  m_next_scene = Scene_id::MAIN_MENU;
}

void App::close(){
  m_running = false;
  reset();
  LOGL("Closing font");
  TTF_CloseFont(m_font);
  LOGL("Closing window");
  m_window->close();
  LOGL("Closing Developer's tools");
  dt.close();
  LOGL("Calling SDL_Quit()");
  SDL_Quit();
  m_scenes_stack.clear();
  m_next_scene = Scene_id::NONE;
  LOGL("Scenes stack cleared");
}


void App::open(){
  m_running = true;
 // Window::Window_Message m = Window::Window_Message::NONE;
  /* running is set to false when App::close() is called.
     Usually within a call of show_scene() */

  while (m_running) {
    while (SDL_PollEvent(&m_event)) {
      if (m_event.type == SDL_WINDOWEVENT) {
        m_window->handle_window_event(m_event);
      }
      else{
        if (dt_open)
          ImGui_ImplSDL2_ProcessEvent(&m_event);
        handle_event();
      }

    }

    if (!m_window->is_open()) {
      LOGL("window has been closed");
      close();
      break;
    }

    // rendering window
    show_scene();

    if (dt_open) {
      m_window->imgui_new_frame();
      dt.show();
      m_window->imgui_render();
    }
    m_window->present();
  }
  LOGL("stop running");
}
void App::show_scene(){
  if(m_next_scene !=m_current_scene )
    LOGL("Rendering scene {}",scene2str(m_next_scene));

  if(m_next_scene ==Scene_id::NONE){
    LOGL("Closing app");
    close();
    return;
  }
  m_current_scene = m_next_scene;


  switch (m_current_scene)
    {
    case Scene_id::MAIN_MENU :
      main_menu();
      break;
    case Scene_id::NEW_GAME:
      new_game();
      break;
    case Scene_id::GAME:
      m_game.render_table();
      break;
    case Scene_id::NONE:
      return;
      break;
    default:
      break;
    }
  SDL_RenderFlush(m_window->get_renderer());
}

void App::handle_event() {
  if (m_current_scene == Scene_id::GAME){
    m_game.handle_event(m_event);
    return;
  }
  const Uint8 *key_state;
  Window::Window_Message wm = Window::Window_Message::NONE;
  switch (m_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
      int x,y;
      SDL_GetMouseState(&x,&y);
      if(m_exit_button.pressed(x,y)){
        LOGL("Exit button pressed");
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
      wm = m_window->handle_window_event(m_event);
      if (wm == Window::Window_Message::WINDOW_CLOSED)
        m_next_scene = Scene_id::NONE;
    case SDL_KEYDOWN:
      key_state = SDL_GetKeyboardState(nullptr);
      if ((key_state[SDL_SCANCODE_LCTRL] || key_state[SDL_SCANCODE_RCTRL]) &&
          key_state[SDL_SCANCODE_Q]) {
        m_next_scene = Scene_id::NONE;
        return;
      } else if((key_state[SDL_SCANCODE_LCTRL]||key_state[SDL_SCANCODE_RCTRL]) & key_state[SDL_SCANCODE_D]){
        dt_open = !dt_open;
        if (!dt_open)
         dt.close();
        return;
      }
      break;
    default:
      break;
        }
}

void App::reset(){
  m_buttons.clear();
  m_window->reset_rendering();
}

void App::main_menu(){
  render_main_menu();
}

void App::render_main_menu(){
  reset();
  m_window->set_render_draw_color(get_colour(Colours::BACKGROUND));
  int w=0,h=0;
  m_window->get_window_center(w,h);
  SDL_Color black = get_colour(Colours::BLACK);
  // title 
  SDL_Rect Title_box{w/2,static_cast<int>(h*(0.25 - 1./14)),w,h/7};
  Text title{m_font,TITLE,black,Title_box,m_window,m_resources};
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
  Text my_profile{m_font,"My Profile",get_colour(Colours::BLACK),temp_box,m_window,m_resources};
  m_buttons.push_back(Button("My Profile",temp_box,m_window,
                             []()-> void {
                              LOGL("My Profile button pressed");
                              std::cout << "My Profile" << std::endl;
                             },m_resources));
  // new game
  temp_box.y = static_cast<int>(my_profile_y-h_off_set);
  Text new_game{m_font,"New Game",get_colour(Colours::BLACK),temp_box,m_window,m_resources};
  m_buttons.push_back(Button("New Game",temp_box,m_window,
                             [this]()->void {
                               LOGL("New game button pressed");
                               this->m_next_scene = Scene_id::NEW_GAME;
                               this->show_scene();
                             }
                             ,m_resources));
  // your Games
  temp_box.y = static_cast<int>(my_profile_y-2*h_off_set);
  Text your_game{m_font,"Your Games",get_colour(Colours::BLACK),temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Your Games",temp_box,m_window,
                             []()->void {
                               LOGL("Your Games button pressed");
                               std::cout << "Your Games" << std::endl;
                             },
                             m_resources));
  // statistic
  temp_box.y = static_cast<int>(my_profile_y+h_off_set);
  Text statistic{m_font,"Statistics",get_colour(Colours::BLACK),temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Statistics",temp_box,m_window,
                             []()->void {
                               LOGL("Statistics button pressed");
                               std::cout << "Statistics" << std::endl;
                             },m_resources));
  // settings
  temp_box.y = static_cast<int>(my_profile_y+2*h_off_set);
  Text setting{m_font,"Settings",get_colour(Colours::BLACK),temp_box,m_window,m_resources};
  m_buttons.push_back(Button("Settings",temp_box,m_window,
                             []()->void {
                               LOGL("Settings button pressed");
                               std::cout << "Settings" << std::endl;
                             },m_resources));
  // close
  temp_box.y = static_cast<int>(my_profile_y+3*h_off_set);
  Text close{m_font,"Exit",get_colour(Colours::BLACK),temp_box,m_window,m_resources};
  m_exit_button= Button("Exit",temp_box,m_window,
                        [this]()->void {
                          LOGL("Exit button pressed");
                          this->m_next_scene = Scene_id::NONE;
                        },m_resources);
//  m_window->present();
}   

void App::new_game(){
  render_new_game();
}

void App::render_new_game(){
  reset();
  m_window->set_render_draw_color(get_colour(Colours::BACKGROUND));
  int w,h;
  m_window->get_window_center(w,h);
  SDL_Rect Title_box{w/2,static_cast<int>(h*(0.25 - 1./14)),w,h/7};
  Text title{m_font,"New Game",get_colour(Colours::BLACK),Title_box,m_window,m_resources};
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
  Text game{m_font,"Ancient Mediterrean",get_colour(Colours::BLACK),box,m_window,m_resources};
  m_buttons.push_back(Button("Ancient Mediterrean",box,m_window,
                             [this]()->void {
                               LOGL("Starting Ancient Mediterrean game");
                               this-> start_game(Game_map::ANCIENT_MEDITERREAN);
                             },m_resources));

  box.y = static_cast<int>(menu_y + h_off_set) ;
  Text back{m_font, "Back", get_colour(Colours::BLACK),box,m_window,m_resources};
  m_exit_button = Button("Back",box,m_window,
                         [this]()->void {
                           LOGL("Back button pressed");
                           this-> m_next_scene=Scene_id::MAIN_MENU;
                         },m_resources);
//
//  m_window->present();
}

void App::start_game(Game_map game){
  LOGL("Starting game");
  m_game.start(game);
  m_next_scene = Scene_id::GAME;
}
