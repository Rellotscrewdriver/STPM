#pragma once

#include "includes.h"
#include "siteOps.h"
/*
#include "addPassSite.h"
#include "removeSite.h"
#include "changeSite.h"
#include "listSite.h"
*/

class dectargs {
public:
  dectargs(std::vector<std::string> &vects) : mArgVect(vects) {
    mArgc = vects.size();
    checkArgs();
  };

private:
  int mArgc;
  int noOfArgsDetect = 2;
  std::vector<std::string> mArgVect;
  bool funcNameCmp(std::string funcName);
  void dectTypeArgs();
  void checkArgs();
  void helpMessage();
  void ArgNumberDetectchangeFeat();
};
