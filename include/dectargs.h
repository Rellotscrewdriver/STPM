#ifndef DECTARGS_H
#define DECTARGS_H

#include "addPassSite.h"
#include <memory>
#include <iostream>
#include <print>
#include <string>
#include <string_view>
#include <cstring>

using namespace std;

class dectargs {
public:
  dectargs(int& cArgs, char* argVect[]) : mArgc(cArgs), mArgVect(argVect) {
    checkArgs();
  };
  ~dectargs();

private:
  int& mArgc;
  char** mArgVect;

  bool funcNameCmp(const char* funcName);
  void checkArgs();
  void dectTypeArgs();
};

#endif