
#include <iostream>
#include <vector>
#include <memory>
#include "../include/app.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

constexpr SDL_Color BACKGROUND{54,220,215,255};
constexpr SDL_Color MENU_COLOR{54,121,220,255};
constexpr SDL_Color WHITE{255,255,255,255};
constexpr SDL_Color BLACK{0,0,0,255};

App::App(){
  if(SDL_Init(SDL_INIT_VIDEO) ==-1) {
    std::cerr <<"Error in initiating SDL, aborting" << std::endl;
    std::cout << SDL_GetError()<< std::endl;
    exit(1);
  }
  if(TTF_Init() == -1){
    std::cerr << "Error in initiationg TTF, aborting"<< std::endl;
    std::cout << TTF_GetError() << std::endl;
  };
  // SDL_CreateWindowAndRenderer(WIDTH*SCALE,HEIGHT*SCALE,0,&window,&renderer);
  m_window = SDL_CreateWindow("Diplomacy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,m_WIDTH*m_SCALE,m_HEIGHT*m_SCALE,SDL_WINDOW_RESIZABLE);
  m_renderer =SDL_CreateRenderer(m_window,1,0);
  m_font = TTF_OpenFont("./fonts/chailce-noggin-font/ChailceNogginRegular.ttf",16 );

  if(m_font==NULL){
    std::cout << "Error: Font not loaded"<< std::endl;
    std::cout << TTF_GetError()<< std::endl;
  }
  SDL_RenderSetScale(m_renderer,m_SCALE,m_SCALE);
  show(Scene_id::MAIN_MENU);
}

App::~App(){
  std::cout << "Deleting app" << std::endl;
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
  default:
    break;
  }
}

void App::render_main_menu(){
  std::cout << "rendering main menu"<< std::endl;
  SDL_SetRenderDrawColor(m_renderer,BACKGROUND.r,BACKGROUND.b,BACKGROUND.g,BACKGROUND.a);
  SDL_RenderClear(m_renderer);
 
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font,"DIPLOMACY",BLACK);
  SDL_Texture* message = SDL_CreateTextureFromSurface(m_renderer,surfaceMessage);
  SDL_Rect  message_rect = SDL_Rect{100,100,200,300};
  Button button = Button(200,200,20,20,"./Images/Button.jpg",m_renderer);
  SDL_RenderCopy(m_renderer,message,NULL,&message_rect);
  SDL_RenderPresent(m_renderer);
  while(SDL_WaitEvent(&m_event)){
    switch (m_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
      int x,y;
      SDL_GetMouseState(&x,&y);
      if(button.pressed(x,y)){
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);
        SDL_Quit();
      }
      break;
    case SDL_QUIT:
      SDL_Quit();
      break;
    default:
      break;
    }
  }
  return;
}   

