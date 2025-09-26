#ifndef LOG_HPP_
#define LOG_HPP_
#include "SDL_stdinc.h"
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

public:
  enum State {
    OPEN = 0x01,
    ENDL = 0x02,
  };

private:
  void headline(std::source_location);
  std::fstream Log;
  uint16_t state = 0x0;
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
    std::cerr << "Error: cannot open log file" << std::endl;
    return;
  }
  state |= State::OPEN;
  state |= State::ENDL;
}


inline Logging::~Logging() {
  Log.close();
  state &= ~State::OPEN;
}

inline void  Logging::headline(std::source_location src) {
  if (!(state & State::ENDL))
    return;
  std::string funcname = src.function_name();
  funcname = funcname.substr(funcname.find_last_of(":") + 1,
                             funcname.find_last_of("(")-1);
  Log   << std::format("[{}: {}] ", src.file_name(), funcname);
}

template <class... Args>
inline void Logging::log(std::source_location src,
                         std::format_string<Args...> fmt, Args &&...args) {
  headline(src);
  Log << std::format(fmt, std::forward<Args>(args)...);
  state &= ~State::ENDL;
};

inline void Logging::log(std::source_location src, const std::string &text) {
  headline(src);
  Log << text;
  state &= ~State::ENDL;
}

template <class... Args>
inline void Logging::log_line(std::source_location src,std::format_string<Args...> fmt, Args &&...args){
  headline(src);
  Log << std::format(fmt, std::forward<Args>(args)...) << std::endl;
  state |= State::ENDL;
}

inline void Logging::log_line(std::source_location src,const std::string &text) {
  headline(src);
  Log << text << std::endl;
  state |= State::ENDL;
}


#endif
