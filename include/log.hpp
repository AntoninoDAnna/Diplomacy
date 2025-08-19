#ifndef LOG_HPP_
#define LOG_HPP_
#include <format>
#include <fstream>
#include <string>
#include <iostream>


class Logging {
public:
  Logging(std::string);
  ~Logging();
  template <class... Args>
  void log(std::format_string<Args...> fmt, Args &&...args);
  void log(const std::string &);

  template <class... Args>
  void log_line(std::format_string<Args...> fmt, Args &&...args);
  void log_line(const std::string&);


private:
  std::fstream Log;
};

#ifdef DEBUG
inline Logging LOG = Logging("../bin/log/logfile.log");
#define LOG(...) LOG.log(__VA_ARGS__)
#define LOGL(...) LOG.log_line(__VA_ARGS__)
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
inline void Logging::log(std::format_string<Args...> fmt, Args &&...args){
  Log << std::format(fmt,std::forward<Args>(args)...);
};

inline void Logging::log(const std::string &text) {
  Log << text;
}

template <class... Args>
inline void Logging::log_line(std::format_string<Args...> fmt, Args &&...args){
  Log <<  std::format(fmt,std::forward<Args>(args)...) << std::endl;
}

inline void Logging::log_line(const std::string &text) {
  Log << text << std::endl;
}


#endif
