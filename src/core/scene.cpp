#include "app_scene.hpp"
#include "core.hpp"

void MainMenu::onRender(){
  m_button.clear();
  m_window->reset_rendering();
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
}

