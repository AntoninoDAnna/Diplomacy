#pragma once

#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>

class Texture_Manager{
  public:
    Texture_Manager(){};
    ~Texture_Manager();
    SDL_Texture* get(const std::string& key){return m_texture_map.at(key);}
    bool haskey(const std::string& key){return m_texture_map.find(key) != m_texture_map.end();}
    void add(const std::string& key, SDL_Texture* t);
    void add(const std::string& key, SDL_Surface* s, SDL_Renderer* r);
    void add(const std::string& key, const std::string& filename, SDL_Renderer* r);
  private:
    std::unordered_map<std::string,SDL_Texture*> m_texture_map;
};

inline Texture_Manager g_TEXTURE; 