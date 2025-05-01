#include "../include/resources_manager.h"
#include "../include/log.h"
#include "../include/globals.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <SDL2/SDL_image.h>



Resources_Manager::Resources_Manager(){
  m_files[g_AM] = map_folder /"Ancient_mediterranean.txt";
} 

Resources_Manager::~Resources_Manager(){
  for(auto [key,val] : m_textures)
    SDL_DestroyTexture(val);
}

void Resources_Manager::add_file(const std::string& key, const std::filesystem::path& filename,std::ostream &log){
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

void Resources_Manager::replace_file(const std::string& key, const std::filesystem::path& filename, std::ostream &log){
  if(!std::filesystem::is_regular_file(filename)){
    log << "Resource Manager error: file "<< filename << "not found: cannot save"<< std::endl;
    return;
  }
  m_files[key]=filename;
  log << "[Resorce Manager] file "<< filename << " added" <<std::endl;

}

void Resources_Manager::remove_file(const std::string& key,std::ostream &log){
  if(!haskey_file(key))
    return;
  auto it = m_files.find(key);
  m_files.erase(it);
  log << "[Resource Manger]: removed file  at key "<< key <<std::endl;
}


std::filesystem::path Resources_Manager::get_file(const std::string& key,std::ostream &log){
    if(!haskey_file(key)){
      log << "Resource Manager error: file "<< key << " is not in resource manager"<<std::endl;
      exit(EXIT_FAILURE);
    }
    return m_files.at(key);
}

SDL_Texture* Resources_Manager::get_texture(const std::string& key,std::ostream &log){
  if(!haskey_texture(key)){
    log<<"Resource Manager error: texture "<< key << " is not in resource manager";
    exit(EXIT_FAILURE);
  }
  return m_textures.at(key);
}


void Resources_Manager::add_texture(const std::string& key, SDL_Texture* t,std::ostream &log){
  if(haskey_texture(key)){
    log << "Resource Manager error: texture "<< key<< " already exists: aborting" << std::endl;
    exit(EXIT_FAILURE);
  }
  m_textures[key] = t;
}
void Resources_Manager::_add(const std::string& key, SDL_Texture* t){
  m_textures[key] = t;
}

void Resources_Manager::add_texture(const std::string& key,SDL_Surface* s, SDL_Renderer* r,std::ostream &log){
  if(haskey_texture(key)){
    log << "Resource Manager error: texture "<< key<< " already exists: aborting" << std::endl;
    exit(EXIT_FAILURE);
  }
  _add(key,SDL_CreateTextureFromSurface(r,s));
  log << "[Resource Manager] Added texture "<< key << std::endl; 
}

void Resources_Manager::add_texture(const std::string& key, const std::filesystem::path& filename,SDL_Renderer* r,std::ostream &log){
  if(haskey_texture(key)){
    log << "Resources Manager error:  texture "<< key <<" already exists: aborting" << std::endl;
    exit(EXIT_FAILURE);
  }
  SDL_Surface* s = IMG_Load(filename.c_str());
  _add(key,SDL_CreateTextureFromSurface(r,s));
  SDL_FreeSurface(s);
  log << "[Resource Manager] Added texture "<< key << std::endl;
}



void Resources_Manager::replace_texture(const std::string& key, SDL_Texture* t,std::ostream &log){
  if(haskey_texture(key)){
    SDL_DestroyTexture(m_textures.at(key));
  }
  _add(key,t);
  log << "[Resource Manager] replaced texture " << key <<std::endl;
}

void Resources_Manager::replace_texture(const std::string& key, SDL_Surface* s, SDL_Renderer* r,std::ostream &log){
  if(haskey_texture(key)){
    SDL_DestroyTexture(m_textures.at(key));
  }
  _add(key,SDL_CreateTextureFromSurface(r,s));
  log << "[Resource Manager] replaced texture " << key <<std::endl;
}

void Resources_Manager::replace_texture(const std::string& key, const std::filesystem::path& filename, SDL_Renderer* r,std::ostream &log){
  SDL_Surface *s = IMG_Load(filename.c_str());
  if( s==NULL){
    log << SDL_GetError() <<std::endl;
    exit(EXIT_FAILURE);  
  } 
  replace_texture(key,s,r);
  SDL_FreeSurface(s);
}


