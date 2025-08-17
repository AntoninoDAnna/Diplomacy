#include "log.hpp"
#include <iostream>

template <class T> void Logging::log(T text){Log << text;};
template <class T> void Logging::log_line(T text) { Log << text << std::endl; };

#ifdef DEBUG
inline Logging LOG  = Logging("../bin/log/logfile.log");
#endif
