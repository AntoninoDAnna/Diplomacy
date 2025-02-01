#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>
#include <vector>

inline std::filesystem::path map_folder = "maps_info";
inline std::filesystem::path img_folder = "Images";
inline std::filesystem::path tiles_folder = "Tiles";
inline std::filesystem::path tiles_file = tiles_folder/"tiles.txt";

class File_Manager{
  public:
    File_Manager();
    ~File_Manager()=default;
    std::filesystem::path get(const std::string& key);
    void add(const std::string& key, const std::filesystem::path& filename);
    void replace(const std::string& key, const std::filesystem::path& filename);
    bool haskey(const std::string& key){return m_files.find(key) != m_files.end();}
    void remove(const std::string& key);
  private:  
    std::unordered_map<std::string,std::filesystem::path> m_files;   
};

inline File_Manager g_FILES;
