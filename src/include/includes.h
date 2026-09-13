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

#if defined(_WIN32)
    // Windows path
    inline const char* localAppDir = std::getenv("LOCALAPPDATA");
    inline const std::string path = ((localAppDir && localAppDir[0] != '\0') ? std::filesystem::path(localAppDir) / "STPM" / "creden.mypass"
    : std::filesystem::path("C:\\STPM\\creden.mypass")).string();
#elif defined(__APPLE__)
    // macOS path
    inline const char* homeConfig = std::getenv("HOME");
    inline const std::string path = ((homeConfig && homeConfig[0] != '\0')
    ? std::filesystem::path(homeConfig) / "Library" / "Application Support" / "STPM" / "creden.mypass"
    : std::filesystem::path(".") / "STPM" / "creden.mypass").string();
#elif defined(__linux__)
    // Linux path, search in XDG_CONFIG_HOME first, then use HOME as fallback
    inline const char* xdgEnv = std::getenv("XDG_CONFIG_HOME");
    inline const char* homeEnv = std::getenv("HOME");
    inline const std::string path = 
    ((xdgEnv && xdgEnv[0] == '/')
        ? std::filesystem::path(xdgEnv) / "STPM" / "creden.mypass"
        : (homeEnv && homeEnv[0] != '\0')
            ? std::filesystem::path(homeEnv) / ".config" / "STPM" / "creden.mypass"
            : std::filesystem::path(".") / "STPM" / "creden.mypass").string();
#else
    #error "Unsupported platform! you tryna compile in BSD or mobile or embedded?"
#endif

//global variable containing data
extern std::vector<siteObj> siteDataNew;

using namespace std;
