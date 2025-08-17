#pragma once
#include <fstream>

#define LOG logfile

inline std::fstream logfile("../bin/log/logfile.log",std::ios_base::out);

