#ifndef WINDOW_H_
#define WINDOW_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include <iostream>
#include "SDL_stdinc.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

class Window{

public:
  enum class Window_Message {
    NONE,
    WINDOW_OPENED,
    WINDOW_CLOSED,
    WINDOW_MINIMIZED,
    WINDOW_MAXIMIZED,
  };
public:
  Window()=default;
  ~Window();


  SDL_Texture* create_texture_from_surface(SDL_Surface* S);
  void close();

  SDL_GLContext get_glcontex(){return m_gl_context;};
  SDL_Renderer* get_renderer(){return m_renderer;};
  void get_renderer_size(int &w, int &h);
  SDL_Window* get_window(){return m_window;};
  void get_window_center(int& x, int& y);
  Uint32 get_window_flags();
  Uint32 get_window_id(){return m_window_id;};
  void get_window_size(int* w, int* h, float* scale);
  Window_Message handle_window_event(SDL_Event&);
  void imgui_init();
  void init(const char *title,
            SDL_WindowFlags wf = static_cast<SDL_WindowFlags>(
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));
  bool is_minimized() { return m_minimized; };
  bool is_shown() { return m_shown; };
  bool is_open(){return m_open;};
  void make_current();
  void minimize();
  void present();
  void render_copy(SDL_Texture* t, const SDL_Rect* src, const SDL_Rect* dst);
  void reset_rendering();
  void restore();
  void set_render_draw_color(SDL_Color C);
  void set_scale(float scale);
  void swap_window();

private:
  // window internal functions

  void create_sdl_window(SDL_WindowFlags);
  void create_sdl_renderer();
  void create_sdl_gl_context();
  void get_glsl_version();
  void destroy_sdl_window();
  void destroy_sdl_renderer();
  void destroy_sdl_gl_context();

  // window data
  Uint32 m_window_id;
  SDL_Window *m_window = NULL;
  SDL_Renderer *m_renderer = NULL;
  SDL_GLContext m_gl_context = NULL;
  ImGuiContext *m_imgui_context = NULL;
  std::string m_title;

  // window position
  int m_x=0,m_y=0;
  // window dimensions
  int m_width = 1280;
  int m_height = 960;
  float m_scale = 1.0;

  //window focus
  bool m_mouse_focus = false;
  bool m_keybord_focus = false;
  bool m_full_screen = false;
  bool m_minimized = false;
  bool m_shown =false;
  bool m_open = false;;

  // GLSL version
  std::string m_glsl_version{};
};



#endif // WINDOW_H_
