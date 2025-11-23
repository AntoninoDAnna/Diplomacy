#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <format>
#include "log.hpp"
#include "globals.hpp"
#include "utilities.hpp"

inline std::filesystem::path map_folder = "maps_info";
inline std::filesystem::path img_folder = "Images";
inline std::filesystem::path tiles_folder = "Tiles";
inline std::filesystem::path tiles_file = tiles_folder/"tiles.txt";
inline std::filesystem::path font_path = "fonts/chailce-noggin-font/ChailceNogginRegular.ttf";

namespace Core{
  class Context;
  
  class Manager{
  public:
    Manager();
    ~Manager();

     std::filesystem::path get_file(const std::string& key);
     void add_file(const std::string& key, const std::filesystem::path& filename);
     void replace_file(const std::string& key, const std::filesystem::path& filename);
     bool haskey_file(const std::string& key){return m_files.find(key) != m_files.end();}
     bool haskey_texture(const std::string& key){return m_textures.find(key) != m_textures.end();}
    
     void remove_file(const std::string& key);
     SDL_Texture* get_texture(const std::string& key);
     void add_texture(const std::string& key, SDL_Texture* t);
     void add_texture(const std::string& key, SDL_Surface* s,Context *ctx);
     void add_texture(const std::string& key, const std::filesystem::path& filename, Context* ctx);
     void replace_texture(const std::string& key, SDL_Texture* t);
     void replace_texture(const std::string& key, SDL_Surface* s, Context* ctx);
     void replace_texture(const std::string& key, const std::filesystem::path& filename, Context* ctx);

  private:
    std::unordered_map<std::string,std::filesystem::path> m_files;
    std::unordered_map<std::string,SDL_Texture*> m_textures;
     void _add(const std::string& key, SDL_Texture* t);
  };


}
