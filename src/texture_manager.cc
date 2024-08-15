#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/texture_manager.h"

Texture_Manager::~Texture_Manager(){
  for(auto [key,val] : m_texture_map)
    SDL_DestroyTexture(val);
}

/*  
 * int Texture_Manager::add(SDL_Texture* t)
 * int Texture_Manager::add(SDL_Surface* s, SDL_Renderer* r)
 * int Texture_Manager::add(const std::string& filename,SDL_Renderer* r)
 * 
 * Adds a texture to the texture manager. If a surface is passed, 
 * the surface has to be freed manually.
 * 
 * It return the id associated to the texture. 
 * 
 */
void Texture_Manager::add(const std::string& key, SDL_Texture* t){
  if(m_texture_map.find(key)!=m_texture_map.end()){
    std::cout << "ERROR: The key already exists: aborting" << std::endl;
    exit(1);
  }
  m_texture_map[key] = t;
}
void Texture_Manager::add(const std::string& key,SDL_Surface* s, SDL_Renderer* r){
  if(m_texture_map.find(key)!=m_texture_map.end()){
    std::cout << "ERROR: The key already exists: aborting" << std::endl;
    exit(1);
  }
  m_texture_map[key] = SDL_CreateTextureFromSurface(r,s);
}

void Texture_Manager::add(const std::string& key, const std::string& filename,SDL_Renderer* r){
  if(m_texture_map.find(key)!=m_texture_map.end()){
    std::cout << "ERROR: The key already exists: aborting" << std::endl;
    exit(1);
  }
  SDL_Surface* s = IMG_Load(filename.c_str());
  m_texture_map[key] = SDL_CreateTextureFromSurface(r,s);
  SDL_FreeSurface(s);
}