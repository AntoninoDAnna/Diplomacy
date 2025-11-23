#ifndef APP_SCENE_HPP
#define APP_SCENE_HPP
#include <array>
#include "core.hpp"

enum class Scene_id{NONE, MAIN_MENU, NEW_GAME,GAME,MY_PROFILE,YOUR_GAMES,STATISTICS,SETTINGS};
enum class Map{NONE, ANCIENT_MEDITERREAN};

struct App_State{
  Scene_id current = Scene_id::NONE;
  Scene_id next = Scene_id::NONE;
  Map map = Map::NONE;
  bool running = false;
  bool dt_open = false;
};


std::unique_ptr<Core::Scene> make_scene(Scene_id,Core::Context* ctx,App_State* as);



class Main_Menu : public Core::Scene{
public:
  Main_Menu(Core::Context* ctx, App_State* as) : Core::Scene("Main Menu",ctx), state(as){}
  //  void on_event(Core::Event& e) override;
  void on_render() override;
private:

private:
  std::array<std::unique_ptr<Core::BButton<void>>,6> buttons;
  App_State* state;
};


class New_Game : public Core::Scene{
public:
  New_Game(Core::Context* ctx, App_State* as) : Core::Scene("New Game",ctx), state(as){}
  // void on_event(Core::Event& e) override;
  // void on_render() override;
private:
  std::vector<std::unique_ptr<Core::BButton<void>>> buttons;
  App_State* state;
};

class My_Profile : public Core::Scene{
public:
  My_Profile(Core::Context* ctx, App_State* as) : Core::Scene("My Profile",ctx), state(as){}
  // void on_event(Core::Event& e) override;
  // void on_render() override;
private:
  App_State* state;
};

class Your_Games : public Core::Scene{
public:
  Your_Games(Core::Context* ctx, App_State* as) : Core::Scene("Your Games",ctx) , state(as){}
  // void on_event(Core::Event& e) override;
  // void on_render() override;
private:
  App_State* state;
};

class Statistics : public Core::Scene{
public:
  Statistics(Core::Context* ctx, App_State* as) : Core::Scene("Statistics",ctx) , state(as){};
  // void on_event(Core::Event& e) override;
  // void on_render() override;
private:
  App_State* state;
};

class Settings : public Core::Scene{
public:
  Settings(Core::Context* ctx, App_State* as) : Core::Scene("Settings",ctx), state(as){};
  // void on_event(Core::Event& e) override {};
  // void on_render() override;
private:
  App_State* state;
};



#endif
