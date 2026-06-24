#pragma once

#include "includes.h"
#include "siteOps.h"

/**
 * A class where the arguments are detected and moves to appropriate operations
 */
class dectargs {
public:
  dectargs(std::vector<std::string> &vects) : mArgVect(vects) {
    mArgc = vects.size();
    checkArgs();
  }

private:
  int mArgc;
  int noOfArgsDetect = 2;
  std::vector<std::string> mArgVect;
  /**
   * A function that compares two enums
   * 
   * @param funcName function name in std::string
   * 
   * @return true if the functions matches, else not
   * 
   * @quote a great man said
   */
  bool funcNameCmp(std::string funcName);
  /**
   * Nothing meow meow
   * 
   * @success you are useless
   */
  void dectTypeArgs();
    /**
   * Nothing meow meow
   * 
   * @warning 
   * you are useless
   */
  void checkArgs();
    /**
   * Nothing meow meow
   * 
   * @example
   * you are useless
   */
  void helpMessage();
  void ArgNumberDetectchangeFeat();
};
