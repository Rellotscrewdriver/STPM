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

const inline std::string path = "add.txt";
const inline std::string tempfile = "temp.txt";

using namespace std;

enum siteOp {
    addSite,
    removeSite,
    listSite,
    changeSiteEmail = 30,
    changeSiteLink,
    changeSiteRegenPass
};