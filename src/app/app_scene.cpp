#include "app_scene.hpp"
#include "core.hpp"
#include "game.hpp"


std::unique_ptr<Core::Scene> make_scene(Scene_id scene, Core::Context* ctx, App_State* state){
  switch(scene){
  case Scene_id::NONE :
    return nullptr;
    break;
  case Scene_id::MAIN_MENU :
    return std::make_unique<Main_Menu>(ctx,state);
    break;
  case Scene_id::NEW_GAME :
    return std::make_unique<New_Game>(ctx,state);
    break;
  case Scene_id::GAME:
    if(state->map == Map::NONE){
	LOGL("Initializing Game but no map specified");
	exit(EXIT_FAILURE);
      }
    return std::make_unique<Game>(ctx,state);
    break;
  case Scene_id::MY_PROFILE :
    LOGL("MY PROFILE REQUESTED BUT NOT DEFINED YET!");
    return make_scene(state->current,ctx,state);
  case Scene_id::YOUR_GAMES :
    LOGL("YOUR GAMES REQUESTED BUT NOT DEFINED YET!");
    return make_scene(state->current,ctx,state);
  case Scene_id::STATISTICS :
    LOGL("STATISTICS REQUESTED BUT NOT DEFINED YET!");
    return make_scene(state->current,ctx,state);
  case Scene_id::SETTINGS :
    LOGL("SETTINGS REQUESTED BUT NOT DEFINED YET!");
    return make_scene(state->current,ctx,state);
  default:
    return nullptr;
  }
  
}

void Main_Menu::on_render(){
  Core::Context* ctx = get_context();
  ctx->m_window.reset_rendering();
  ctx->m_window.set_render_draw_color(get_colour(Core::Colours::BACKGROUND));
  int w=0,h=0;
  ctx->m_window.get_window_center(w,h);
  SDL_Color black = get_colour(Core::Colours::BLACK);
  // title 
  SDL_Rect Title_box{w/2,static_cast<int>(h*(0.25 - 1./14)),w,h/7};
  Core::Text title{"BETRAYAL",black,Title_box,ctx};
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
  Core::Text my_profile{"My Profile",black,temp_box,ctx};
  buttons[0]= std::make_unique<Core::Button>("My Profile",temp_box,
                             []()-> void {
                              LOGL("My Profile button pressed");
                              std::cout << "My Profile" << std::endl;
                             },ctx);
  // new game
  temp_box.y = static_cast<int>(my_profile_y-h_off_set);
  Core::Text new_game{"New Game",black,temp_box,ctx};
  buttons[1] = std::make_unique<Core::Button>("New Game",temp_box,
					      [this]()->void {
						this->state->next = Scene_id::NEW_GAME;
					      },ctx);
  // your Games
  temp_box.y = static_cast<int>(my_profile_y-2*h_off_set);
  Core::Text your_game{"Your Games",black,temp_box,ctx};
  buttons[2] = std::make_unique<Core::Button>("Your Games",temp_box,
                             []()->void {
                               LOGL("Your Games button pressed");
                               std::cout << "Your Games" << std::endl;
                             },ctx);
  // statistic
  temp_box.y = static_cast<int>(my_profile_y+h_off_set);
  Core::Text statistic{"Statistics",black,temp_box,ctx};
buttons[3] = std::make_unique<Core::Button>("Statistics",temp_box,
                             []()->void {
                               LOGL("Statistics button pressed");
                               std::cout << "Statistics" << std::endl;
                             },ctx);
  // settings
  temp_box.y = static_cast<int>(my_profile_y+2*h_off_set);
  Core::Text setting{"Settings",black,temp_box,ctx};
buttons[4] = std::make_unique<Core::Button>("Settings",temp_box,
                             []()->void {
                               LOGL("Settings button pressed");
                               std::cout << "Settings" << std::endl;
                             },ctx);
  // close
  temp_box.y = static_cast<int>(my_profile_y+3*h_off_set);
  Core::Text close{"Exit",black,temp_box,ctx};
buttons[5] = std::make_unique<Core::Button>("Exit",temp_box,
                        [this]()->void {
                          LOGL("Exit button pressed");
                          this->state->next = Scene_id::NONE;
                        },ctx);  
}

