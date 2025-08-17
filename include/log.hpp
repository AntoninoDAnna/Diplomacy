#ifndef LOG_HPP_
#define LOG_HPP_
#include <fstream>
#include <string>


#ifdef DEBUG
#define LOG(...) LOG.log(__VA_ARGS__)
#define LOGL(...) LOG.log_line(__VA_ARGS__)
#else
#define LOG(...)
#define LOGL(...)
#endif

class Logging {
public:
  Logging(std::string);
  ~Logging();
  template <class T> void log(T);
  template <class T> void log_line(T);
private:
  std::fstream Log;
};
#endif
