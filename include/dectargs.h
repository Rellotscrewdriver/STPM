#ifndef DECTARGS_H
#define DECTARGS_H

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

  void checkArgs();
  void dectTypeArgs();
};

#endif