#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>

inline std::filesystem::path map_folder = "maps_info";
inline std::filesystem::path img_folder = "Images";
inline std::filesystem::path tiles_folder = "Tiles";
inline std::filesystem::path tiles_file = tiles_folder/"tiles.txt";

class Resources_Manager{
  public:
    Resources_Manager();
    ~Resources_Manager();

    std::filesystem::path get_file(const std::string& key,std::ostream &log = std::cout);
    void add_file(const std::string& key, const std::filesystem::path& filename,std::ostream &log=std::cout);
    void replace_file(const std::string& key, const std::filesystem::path& filename,std::ostream &log=std::cout);
    bool haskey_file(const std::string& key){return m_files.find(key) != m_files.end();}
    bool haskey_texture(const std::string& key){return m_textures.find(key) != m_textures.end();}
    
    void remove_file(const std::string& key,std::ostream &log=std::cout);
    SDL_Texture* get_texture(const std::string& key,std::ostream &log=std::cout);

    /*  
     * void Resources_Manager::add(const std::string& key, SDL_Texture* t)
     * void Resources_Manager::add(const std::string& key, SDL_Surface* s, SDL_Renderer* r)
     * void Resources_Manager::add(const std::string& key, const std::string& filename,SDL_Renderer* r)
     * 
     * Adds a texture to the texture manager.
     * If `key` already exists prints an error message and abort;
     * If a surface is passed, it has to be freed manually.
     * 
     */
    void add_texture(const std::string& key, SDL_Texture* t,std::ostream &log=std::cout);
    void add_texture(const std::string& key, SDL_Surface* s, SDL_Renderer* r,std::ostream &log=std::cout);
    void add_texture(const std::string& key, const std::filesystem::path& filename, SDL_Renderer* r,std::ostream &log=std::cout);
    /* 
     * void replace(const std::string& key, SDL_Texture* t);
     * void replace(const std::string& key, SDL_Surface* s, SDL_Renderer* r);
     * void replace(const std::string& key, const std::string& filename, SDL_Renderer* r);
     * 
     * replace the texture corresponding to `key`. If `key` does not exitst, it adds the texture
     * 
     */
    void replace_texture(const std::string& key, SDL_Texture* t,std::ostream &log=std::cout);
    void replace_texture(const std::string& key, SDL_Surface* s, SDL_Renderer* r,std::ostream &log=std::cout);
    void replace_texture(const std::string& key, const std::filesystem::path& filename, SDL_Renderer* r,std::ostream &log=std::cout);


  private:  
    std::unordered_map<std::string,std::filesystem::path> m_files;   
    std::unordered_map<std::string,SDL_Texture*> m_textures;   

  /*
     *  void _add(const std::string& key, SDL_Texture* t);  
     * 
     *  Adds a texture without checking if 'key' already exists. 
     * 
     */
    void _add(const std::string& key, SDL_Texture* t);
};

