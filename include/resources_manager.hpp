#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "log.hpp"
#include "globals.hpp"
#include "utilities.hpp"

inline std::filesystem::path map_folder = "maps_info";
inline std::filesystem::path img_folder = "Images";
inline std::filesystem::path tiles_folder = "Tiles";
inline std::filesystem::path tiles_file = tiles_folder/"tiles.txt";

class Resources_Manager{
public:
  Resources_Manager();
  ~Resources_Manager();

  inline std::filesystem::path get_file(const std::string& key,std::ostream &log = std::cout);
  inline void add_file(const std::string& key, const std::filesystem::path& filename,std::ostream &log=std::cout);
  inline void replace_file(const std::string& key, const std::filesystem::path& filename,std::ostream &log=std::cout);
  inline bool haskey_file(const std::string& key){return m_files.find(key) != m_files.end();}
  inline bool haskey_texture(const std::string& key){return m_textures.find(key) != m_textures.end();}
    
  inline void remove_file(const std::string& key,std::ostream &log=std::cout);
  inline SDL_Texture* get_texture(const std::string& key,std::ostream &log=std::cout);

  /*
   * void Resources_Manager::add(const std::string& key, SDL_Texture* t,std::ostream &log=std::cout)
   * template<class T>
   * void Resources_Manager::add(const std::string& key, SDL_Surface* s, T& window, std::ostream &log=std::cout)
   * template <class T>
   * void Resources_Manager::add(const std::string& key, const std::string& filename,T& window,std::ostream &log=std::cout)
   *
   * Adds a texture to the texture manager.
   * If `key` already exists prints an error message and abort;
   * If a surface is passed, it has to be freed manually.
   *
   * `T& window`  must be a (smart) pointer to a window instance
   */
  inline void add_texture(const std::string& key, SDL_Texture* t,std::ostream &log=std::cout);
  template<class T>
  inline void add_texture(const std::string& key, SDL_Surface* s, T& window ,std::ostream &log=std::cout);
  template <class T>
  inline void add_texture(const std::string& key, const std::filesystem::path& filename,T& window,std::ostream &log=std::cout);
  /*
   * void replace(const std::string& key, SDL_Texture* t);
   * template <class T>
   * void replace(const std::string& key, SDL_Surface* s, T& window);
   * template <class T>
   * void replace(const std::string& key, const std::string& filename, T& window);
   *
   * replace the texture corresponding to `key`. If `key` does not exitst, it adds the texture
   *
   * `T& window` must be a (smart) pointer to a window instance
   */
  inline void replace_texture(const std::string& key, SDL_Texture* t,std::ostream &log=std::cout);
  template <class T>
  inline void replace_texture(const std::string& key, SDL_Surface* s, T& window,std::ostream &log=std::cout);
  template <class T>
  inline void replace_texture(const std::string& key, const std::filesystem::path& filename, T& window,std::ostream &log=std::cout);


private:
  std::unordered_map<std::string,std::filesystem::path> m_files;
  std::unordered_map<std::string,SDL_Texture*> m_textures;

  /*
   *  void _add(const std::string& key, SDL_Texture* t);
   *
   *  Adds a texture without checking if 'key' already exists.
   *
   */
  inline void _add(const std::string& key, SDL_Texture* t);
};

inline Resources_Manager::Resources_Manager(){
  m_files[g_AM] = map_folder /"Ancient_mediterranean.txt";
}

inline Resources_Manager::~Resources_Manager(){
  for(auto [key,val] : m_textures)
    SDL_DestroyTexture(val);
}

inline void Resources_Manager::add_file(const std::string& key, const std::filesystem::path& filename,std::ostream &log){
  if(haskey_file(key)){
    log<<"Resource Manager error: file  "<< key<< " already exist, cannot override"<<std::endl;
    return;
  }
  if(!std::filesystem::is_regular_file(filename)){
    log << "Resource Manager error: file "<< filename << "not found: cannot save"<< std::endl;
    return;
  }
  m_files[key] = filename;
  log << "[Resorce Manager] file "<< filename << " added" <<std::endl;
}

inline void Resources_Manager::replace_file(const std::string& key, const std::filesystem::path& filename, std::ostream &log){
  if(!std::filesystem::is_regular_file(filename)){
    log << "Resource Manager error: file "<< filename << "not found: cannot save"<< std::endl;
    return;
  }
  m_files[key]=filename;
  log << "[Resorce Manager] file "<< filename << " added" <<std::endl;

}

inline void Resources_Manager::remove_file(const std::string& key,std::ostream &log){
  if(!haskey_file(key))
    return;
  auto it = m_files.find(key);
  m_files.erase(it);
  log << "[Resource Manger]: removed file  at key "<< key <<std::endl;
}


inline std::filesystem::path Resources_Manager::get_file(const std::string& key,std::ostream &log){
  if(!haskey_file(key)){
    log << "Resource Manager error: file "<< key << " is not in resource manager"<<std::endl;
    exit(EXIT_FAILURE);
  }
  return m_files.at(key);
}

inline SDL_Texture* Resources_Manager::get_texture(const std::string& key,std::ostream &log){
  if(!haskey_texture(key)){
    log<<"Resource Manager error: texture "<< key << " is not in resource manager";
    exit(EXIT_FAILURE);
  }
  return m_textures.at(key);
}


inline void Resources_Manager::add_texture(const std::string& key, SDL_Texture* t,std::ostream &log){
  if(haskey_texture(key)){
    log << "Resource Manager error: texture "<< key<< " already exists: aborting" << std::endl;
    exit(EXIT_FAILURE);
  }
  m_textures[key] = t;
}

inline void Resources_Manager::_add(const std::string& key, SDL_Texture* t){
  m_textures[key] = t;
}

template <class T>
inline void Resources_Manager::add_texture(const std::string& key,SDL_Surface* s, T& window,std::ostream &log){
  static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>, "Error: window must be a (smart) pointer");
  if(haskey_texture(key)){
    log << "Resource Manager error: texture "<< key<< " already exists: aborting" << std::endl;
    exit(EXIT_FAILURE);
  }
  _add(key,window->create_texture_from_surface(s));
  log << "[Resource Manager] Added texture "<< key << std::endl;
}

template <class T>
inline void Resources_Manager::add_texture(const std::string& key, const std::filesystem::path& filename,T& window,std::ostream &log){
  static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>, "Error: window must be a (smart) pointer");
  if(haskey_texture(key)){
    log << "Resources Manager error:  texture "<< key <<" already exists: aborting" << std::endl;
    exit(EXIT_FAILURE);
  }
  SDL_Surface* s = IMG_Load(filename.c_str());
  if( s==NULL){
    log << SDL_GetError() <<std::endl;
    exit(EXIT_FAILURE);
  }
  _add(key,window->create_texture_from_surface(s));
  SDL_FreeSurface(s);
  log << "[Resource Manager] Added texture "<< key << std::endl;
}

inline void Resources_Manager::replace_texture(const std::string& key, SDL_Texture* t,std::ostream &log){
  if(haskey_texture(key)){
    SDL_DestroyTexture(m_textures.at(key));
  }
  _add(key,t);
  log << "[Resource Manager] replaced texture " << key <<std::endl;
}

template <class T>
inline void Resources_Manager::replace_texture(const std::string& key, SDL_Surface* s, T& window,std::ostream &log){
  static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>, "Error: window must be a (smart) pointer");
  if(haskey_texture(key)){
    SDL_DestroyTexture(m_textures.at(key));
  }
  _add(key,window->create_texture_from_surface(s));
  log << "[Resource Manager] replaced texture " << key <<std::endl;
}

template <class T>
inline void Resources_Manager::replace_texture(const std::string& key, const std::filesystem::path& filename, T& window,std::ostream &log){
  static_assert(std::is_pointer_v<T> || Util::is_smart_pointer_v<T>, "Error: window must be a (smart) pointer");
  SDL_Surface *s = IMG_Load(filename.c_str());
  if( s==NULL){
    log << SDL_GetError() <<std::endl;
    exit(EXIT_FAILURE);
  }
  _add(key,window->create_texture_from_surface(s));
  SDL_FreeSurface(s);
}
