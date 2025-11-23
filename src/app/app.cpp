#include <iostream>
#include <vector>
#include "app.hpp"
#include "core.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "SDL2/SDL.h"

void App::init() {
  LOGL("Initializing App");
  ctx.init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
  ctx.init_window("DIPLOMACY",SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_MAXIMIZED);
  dt.share_ctx(&ctx);
  dt.init();
  m_state.next =  Scene_id::MAIN_MENU;
}

void App::close(){
  m_state.running = false;
  reset();
}

void App::open(){
  m_state.running = true;
 // Window::Window_Message m = Window::Window_Message::NONE;
  /* running is set to false when App::close() is called.
     Usually within a call of show_scene() */

  while (m_state.running) {
    while (SDL_PollEvent(&m_event)) {
      if (m_event.type == SDL_WINDOWEVENT) {
        ctx.m_window.handle_window_event(m_event);
      }
      else{
        if (m_state.dt_open)
          ImGui_ImplSDL2_ProcessEvent(&m_event);

	scene->on_event(m_event);
      }

    }

    if (!ctx.m_window.is_open()) {
      LOGL("window has been closed");
      close();
      break;
    }

    // rendering window
    show_scene();

    if (m_state.dt_open) {
      ctx.m_window.imgui_new_frame();
      dt.show();
      ctx.m_window.imgui_render();
    }
    ctx.m_window.present();
  }
  LOGL("stop running");
}
void App::show_scene(){
  if(m_state.next ==Scene_id::NONE){
    LOGL("Closing app");
    close();
    return;
  }

  m_state.current = m_state.next;

  scene = make_scene(m_state.current,&ctx,&m_state);
  
  if(scene == nullptr){
    LOGL("rendering nullptr scene!");
    exit(EXIT_FAILURE);
  }

  scene->on_render();
  SDL_RenderFlush(ctx.m_window.get_renderer());
}

void App::reset(){
  ctx.m_window.reset_rendering();
}

