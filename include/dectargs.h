#pragma once

#include "includes.h"
#include "addPassSite.h"
#include "removeSite.h"
#include "changeSite.h"
#include "listSite.h"

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
  void ArgNumberDetectchangeFeat();
};
