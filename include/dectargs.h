#ifndef DECTARGS_H
#define DECTARGS_H

#include "genPass.h"
#include <memory>
#include <iostream>
#include <print>
#include <string>
#include <string_view>
#include <cstring>
class dectargs {
public:
  dectargs(int& cArgs, char* argVect[]) : mArgc(cArgs), mArgVect(argVect) {
    checkArgs();
  };

private:
  int& mArgc;
  char** mArgVect;

  GeneratePass pass;
  bool funcNameCmp(const char* funcName);
  void checkArgs();
  void dectTypeArgs();
};

#endif