#ifndef LOG_HPP_
#define LOG_HPP_
#include <format>
#include <fstream>
#include <string>
#include <iostream>
#include <source_location>


class Logging {
public:
  Logging(std::string);
  ~Logging();
  template <class... Args>
  void log(std::source_location, std::format_string<Args...> fmt, Args &&...args);
  void log(std::source_location, const std::string &);

  template <class... Args>
  void log_line(std::source_location, std::format_string<Args...> fmt, Args &&...args);
  void log_line(std::source_location, const std::string&);


private:
  std::fstream Log;
};

#ifdef DEBUG
inline Logging LOG = Logging("../bin/log/logfile.log");
#define LOG(...) LOG.log(std::source_location::current(), __VA_ARGS__)
#define LOGL(...) LOG.log_line(std::source_location::current(), __VA_ARGS__)
#else
#define LOG(...)
#define LOGL(...)
#endif


inline Logging::Logging(std::string filename) {
  Log.open(filename, std::ios_base::out);
  if (!Log.is_open()) {
    std::cerr << "Error: cannot open log file"<<std::endl;
  }
}

inline Logging::~Logging() {
  Log.close();
}

template <class... Args>
inline void Logging::log(std::source_location src, std::format_string<Args...> fmt, Args &&...args){
  Log << std::format("[{},{}] {}", src.file_name(), src.function_name(),
                     std::format(fmt, std::forward<Args>(args)...)
                     );
};

inline void Logging::log(std::source_location src,const std::string &text) {
  Log << std::format("[{},{}] {}", src.file_name(), src.function_name(),
                     text
                     );
}

template <class... Args>
inline void Logging::log_line(std::source_location src,std::format_string<Args...> fmt, Args &&...args){
  Log << std::format("[{},{}] {}", src.file_name(), src.function_name(),
                     std::format(fmt, std::forward<Args>(args)...)
                     ) << std::endl;
}

inline void Logging::log_line(std::source_location src,const std::string &text) {
  Log << std::format("[{},{}] {}", src.file_name(), src.function_name(),
                     text
                     ) << std::endl;
}


#endif
