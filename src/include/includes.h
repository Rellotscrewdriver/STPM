#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <string_view>
#include <cstring>
#include <fstream>
#include <random>
#include <iomanip>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include "siteObj.h"

inline const std::string path = "creden.mypass";
inline const std::string tempfile = "temp.db";

extern std::vector<siteObj> siteDataNew;

using namespace std;
