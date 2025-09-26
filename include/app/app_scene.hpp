#ifndef APP_SCENE_HPP
#define APP_SCENE_HPP
#include "core.hpp"
#include <memory>

enum class Scene_id{NONE, MAIN_MENU, NEW_GAME,GAME};
std::unique_ptr<Core::Scene> make_scene(Scene_id);

class MainMenu : Core::Scene{
public:
  MainMenu() : Core::Scene("Main Menu"){}
  void on_event(Core::Event& e) ;
  void on_render() override;

private:
  std::vector<Core::Button> m_button;
  std::shared_ptr<Core::Window> m_window;
};

class NewGame : Core::Scene{
public:
  NewGame() : Core::Scene("New Game"){}
  void on_event(Core::Event& e) override;
  void on_render() override;
};

class MyProfile : Core::Scene{
public:
  MyProfile() : Core::Scene("My Profile"){}
  void on_event(Core::Event& e) override;
  void on_render() override;
};

class YourGames : Core::Scene{
public:
  YourGames() : Core::Scene("Your Games") {}
  void on_event(Core::Event& e) override;
  void on_render() override;
};

class Statistics : Core::Scene{
public:
  Statistics() : Core::Scene("Statistics") {};
  void on_event(Core::Event& e) override;
  void on_render() override;
};

class Settings : Core::Scene{
public:
  Settings() : Core::Scene("Settings"){};
  void on_event(Core::Event& e) override {};
  void on_render() override;
};



#endif
