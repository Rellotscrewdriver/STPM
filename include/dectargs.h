#ifndef DECTARGS_H
#define DECTARGS_H

#include "includes.h"
#include "addPassSite.h"

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