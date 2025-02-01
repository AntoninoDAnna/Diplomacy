#include "../include/file_manager.h"
#include "../include/log.h"
#include "../include/game.h"
#include <iostream>
#include <string>
#include <filesystem>



File_Manager::File_Manager(){
  m_files[g_AM] = map_folder /"Ancient_mediterranean.txt";
} 

void File_Manager::add(const std::string& key, const std::filesystem::path& filename){
  if(haskey(key)){
    LOG<<"File Manager error: Key "<< key<< " already exist, cannot override"<<std::endl;
    return;
  }
  if(!std::filesystem::is_regular_file(filename)){
    LOG << "File Manager error: file "<< filename << "not found: cannot save"<< std::endl;
    return;
  }
  m_files[key] = filename;

}

void File_Manager::replace(const std::string& key, const std::filesystem::path& filename){
  if(!std::filesystem::is_regular_file(filename)){
    LOG << "File Manager error: file "<< filename << "not found: cannot save"<< std::endl;
    return;
  }
  m_files[key]=filename;
}

void File_Manager::remove(const std::string& key){
  if(!haskey(key))
    return;
  auto it = m_files.find(key);
  m_files.erase(it);
}


std::filesystem::path File_Manager::get(const std::string& key){
    if(!haskey(key)){
      LOG << key << " is not in file manager"<<std::endl;
      exit(EXIT_FAILURE);
    }
    return m_files.at(key);
}