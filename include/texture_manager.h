#pragma once

#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>

class Texture_Manager{
  public:
    Texture_Manager(){};
    ~Texture_Manager();
    Texture_Manager(const Texture_Manager& t) = delete;
    SDL_Texture* get(const std::string& key);
    bool haskey(const std::string& key){return m_texture_map.find(key) != m_texture_map.end();}
    
    /*  
     * void Texture_Manager::add(const std::string& key, SDL_Texture* t)
     * void Texture_Manager::add(const std::string& key, SDL_Surface* s, SDL_Renderer* r)
     * void Texture_Manager::add(const std::string& key, const std::string& filename,SDL_Renderer* r)
     * 
     * Adds a texture to the texture manager.
     * If `key` already exists prints an error message and abort;
     * If a surface is passed, it has to be freed manually.
     * 
     */
    void add(const std::string& key, SDL_Texture* t);
    void add(const std::string& key, SDL_Surface* s, SDL_Renderer* r);
    void add(const std::string& key, const std::string& filename, SDL_Renderer* r);
    /* 
     * void replace(const std::string& key, SDL_Texture* t);
     * void replace(const std::string& key, SDL_Surface* s, SDL_Renderer* r);
     * void replace(const std::string& key, const std::string& filename, SDL_Renderer* r);
     * 
     * replace the texture corresponding to `key`. If `key` does not exitst, it adds the texture
     * 
     */
    
    void replace(const std::string& key, SDL_Texture* t);
    void replace(const std::string& key, SDL_Surface* s, SDL_Renderer* r);
    void replace(const std::string& key, const std::string& filename, SDL_Renderer* r);

  private:
    std::unordered_map<std::string,SDL_Texture*> m_texture_map;
  private:
    /*
     *  void _add(const std::string& key, SDL_Texture* t);  
     *  void _add(const std::string& key, SDL_Surface* s, SDL_Renderer* r);  
     *  void _add(const std::string& key, const std::string& filename, SDL_Renderer* r);  
     * 
     *  Adds a texture without checking if 'key' already exists. 
     * 
     */
    void _add(const std::string& key, SDL_Texture* t);
    void _add(const std::string& key, SDL_Surface* s, SDL_Renderer* r);
    void _add(const std::string& key, const std::string& filename, SDL_Renderer* r);

};

inline Texture_Manager g_TEXTURE; 