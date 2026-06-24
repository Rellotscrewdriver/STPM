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
#include "rapidcsv.h"

constinit inline std::string path = "add.txt";
constinit inline std::string tempfile = "temp.txt";
//std::vector<siteObj> meow;
static std::vector<std::string> siteData;

using namespace std;

enum siteOp {
    addSite,
    removeSite,
    listSite,
    changeSiteEmail = 30,
    changeSiteLink,
    changeSiteRegenPass
};