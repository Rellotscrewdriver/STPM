#ifndef DECTARGS_H
#define DECTARGS_H

#include "genPass.h"
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

  GeneratePass *pass = new GeneratePass();
  bool funcNameCmp(const char* funcName);
  void checkArgs();
  void dectTypeArgs();
};

#endif