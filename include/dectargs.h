#ifndef DECTARGS_H
#define DECTARGS_H

#include "addPassSite.h"
#include "removeSite.h"
#include <memory>
#include <iostream>
#include <string>
#include <string_view>
#include <cstring>

using namespace std;

class dectargs {
public:
  dectargs(int& cArgs, char* argVect[]) : mArgc(cArgs), mArgVect(argVect) {
    checkArgs();
  };

private:
  int& mArgc;
  char** mArgVect;
  std::string tempVal;
  bool funcNameCmp(std::string funcName);
  void dectTypeArgs();
  void checkArgs();
  void helpMessage();
};

#endif