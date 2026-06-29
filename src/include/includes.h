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

constinit inline std::string path = "creden.mypass";
constinit inline std::string tempfile = "temp.db";

extern std::vector<std::string> siteData;
extern std::vector<siteObj> siteDataNew;


using namespace std;

enum siteOp {
    addSite,
    removeSite,
    listSite,
    changeSiteEmail = 30,
    changeSiteLink,
    changeSiteRegenPass
};