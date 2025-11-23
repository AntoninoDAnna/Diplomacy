#include "manager.hpp"
#include "core.hpp"

namespace Core{
  Manager::Manager(){
    m_files[g_AM] = map_folder /"Ancient_mediterranean.txt";
  }

  Manager::~Manager(){
    for(auto [key,val] : m_textures)
      SDL_DestroyTexture(val);
  }

  void Manager::add_file(const std::string& key, const std::filesystem::path& filename){
    if(haskey_file(key)){
      LOGL("Resource Manager error: file {} already exist, cannot override",key);
      return;
    }
    if(!std::filesystem::is_regular_file(filename)){
      LOGL("Resource Manager error: file {} not found: cannot save",filename.string());
      return;
    }
    m_files[key] = filename;
    LOGL("[Resorce Manager] file {} added", filename.string());
  }

  void Manager::replace_file(const std::string& key, const std::filesystem::path& filename){
    if(!std::filesystem::is_regular_file(filename)){
      LOGL("Resource Manager error: file {} not found: cannot save",filename.string());
      return;
    }
    m_files[key]=filename;
    LOGL("[Resorce Manager] file {} added", filename.string());

  }

  void Manager::remove_file(const std::string& key){
    if(!haskey_file(key))
      return;
    auto it = m_files.find(key);
    m_files.erase(it);
    LOGL("[Resource Manger]: removed file  at key {} ", key);
  }


  std::filesystem::path Manager::get_file(const std::string& key){
    if (!haskey_file(key)) {
      LOGL("[Resource Manager]: file {} is not in resource manager", key);
      exit(EXIT_FAILURE);
    }
    return m_files.at(key);
  }

  SDL_Texture* Manager::get_texture(const std::string& key){
    if (!haskey_texture(key)) {
      LOGL("[Resource Manager]: texture {} is not in resource manager",key);
      exit(EXIT_FAILURE);
    }
    return m_textures.at(key);
  }


  void Manager::add_texture(const std::string& key, SDL_Texture* t){
    if (haskey_texture(key)) {
      LOGL("[Resource Manager]: texture {} already exists. Aborting",key);
      exit(EXIT_FAILURE);
    }
    m_textures[key] = t;
  }

  void Manager::_add(const std::string& key, SDL_Texture* t){
    m_textures[key] = t;
  }

  void Manager::add_texture(const std::string& key,SDL_Surface* s, Context* ctx){
    if(haskey_texture(key)){
      LOGL("[Resource Manager]: texture {} already exists. Aborting",key);
      exit(EXIT_FAILURE);
    }
    _add(key,ctx->m_window.create_texture_from_surface(s));
    LOGL("[Resource Manager]: Added texture {}", key);
  }

  void Manager::add_texture(const std::string& key, const std::filesystem::path& filename, Context* ctx){
    if(haskey_texture(key)){
      LOGL("[Resource Manager]: texture {} already exists. Aborting",key);
      exit(EXIT_FAILURE);
    }
    SDL_Surface* s = IMG_Load(filename.c_str());
    if( s==NULL){
      LOGL(SDL_GetError());
      exit(EXIT_FAILURE);
    }
    _add(key,ctx->m_window.create_texture_from_surface(s));
    SDL_FreeSurface(s);
    LOGL("[Resource Manager]: Added texture {}", key);
  }

  void Manager::replace_texture(const std::string& key, SDL_Texture* t){
    if(haskey_texture(key)){
      SDL_DestroyTexture(m_textures.at(key));
    }
    _add(key,t);
    LOGL("[Resource Manages]: Replaced texture {}", key);
  }

  void Manager::replace_texture(const std::string& key, SDL_Surface* s, Context* ctx){
    if(haskey_texture(key)){
      SDL_DestroyTexture(m_textures.at(key));
    }
    _add(key,ctx->m_window.create_texture_from_surface(s));
    LOGL(SDL_GetError());
  }

  void Manager::replace_texture(const std::string& key, const std::filesystem::path& filename, Context* ctx){
    SDL_Surface *s = IMG_Load(filename.c_str());
    if( s==NULL){
      LOGL(SDL_GetError());
      exit(EXIT_FAILURE);
    }
    _add(key,ctx->m_window.create_texture_from_surface(s));
    SDL_FreeSurface(s);
  }
}
