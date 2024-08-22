#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/texture_manager.h"
#include "../include/log.h"
Texture_Manager::~Texture_Manager(){
  for(auto [key,val] : m_texture_map)
    SDL_DestroyTexture(val);
}


void Texture_Manager::add(const std::string& key, SDL_Texture* t){
  if(haskey(key)){
    LOG << "ERROR: The key "<< key<< " already exists: aborting" << std::endl;
    exit(1);
  }
  m_texture_map[key] = t;
}
void Texture_Manager::_add(const std::string& key, SDL_Texture* t){
  m_texture_map[key] = t;
}

void Texture_Manager::add(const std::string& key,SDL_Surface* s, SDL_Renderer* r){
  if(haskey(key)){
    LOG << "ERROR: The key "<< key<< " already exists: aborting" << std::endl;
    exit(1);
  }
  _add(key,SDL_CreateTextureFromSurface(r,s));
}

void Texture_Manager::add(const std::string& key, const std::string& filename,SDL_Renderer* r){
  if(haskey(key)){
    LOG << "ERROR: The key already exists: aborting" << std::endl;
    exit(1);
  }
  SDL_Surface* s = IMG_Load(filename.c_str());
  _add(key,SDL_CreateTextureFromSurface(r,s));
  SDL_FreeSurface(s);
}


SDL_Texture* Texture_Manager::get(const std::string& key){
  if(this->haskey(key))
    return m_texture_map.at(key);
  
  return NULL;
}

void Texture_Manager::replace(const std::string& key, SDL_Texture* t){
  if(haskey(key)){
    SDL_DestroyTexture(m_texture_map.at(key));
    m_texture_map[key]=t;
    return;
  }
  _add(key,t);
}

void Texture_Manager::replace(const std::string& key, SDL_Surface* s, SDL_Renderer* r){
  replace(key,SDL_CreateTextureFromSurface(r,s));
}

void Texture_Manager::replace(const std::string& key, const std::string& filename, SDL_Renderer* r){
  LOG << "replacing "<< filename << std::endl;
  SDL_Surface *s = IMG_Load(filename.c_str());
  if( s==NULL) LOG << SDL_GetError() <<std::endl;  
  replace(key,s,r);
  SDL_FreeSurface(s);
}
