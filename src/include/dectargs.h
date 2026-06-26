#pragma once

#include "includes.h"
#include "siteOps.h"
/*
#include "addPassSite.h"
#include "removeSite.h"
#include "changeSite.h"
#include "listSite.h"
*/

/**
 * This class handles the incoming calls of commandline arguements
 * if no arguements are given, then this class calls the TUI frontend
 */
class dectargs {
public:
  /**
   * This constructor takes a vector of arguements and selects the appropriate destination
   * 
   * @param vects 
   * a string vector containing the main operation and then it's subcommands
   * 
   * @example
   * the vector must statisfy at least one condition, mode, 
   * ```cpp
   * dectargs({"add", "test@gmail.com", "website.io"});
   * ```
   */
  dectargs(std::vector<std::string> &vects) : mArgVect(vects) {
    mArgc = vects.size();
    checkArgs();
  };

private:
  int mArgc;
  /**
   * max no of arguements that a mode can have
   */
  int noOfArgsDetect = 2;

  std::vector<std::string> mArgVect;
  /**
   * compares the first commandline arguement to given parameter
   * 
   * @param modeName 
   * a string containing an operation
   * 
   * @return 
   * true if it matches, false if it don't match
   */
  bool funcNameCmp(std::string funcName);

  /**
   * select the type which the arguement is given
   * 
   * @danger 
   * this function can crash the entire program if no commandline arguements are given 
   */
  void dectTypeArgs();
  
  /**
   * shields the dectTypeArgs() function if too many or too low arguements are given
   * 
   * @info 
   * this is also where the TUI frontend is gonna be executed when no arguements are given
   */
  void checkArgs();

  /**
   * simply prints the help message when putting "help"
   */
  void helpMessage();
  
  /**
   * check the no of arguement to determine whether 
   * the user wants to regenerate the password or rename a site link or email
   * 
   * @warning 
   * this function is only used for change arguement
   */
  void ArgNumberDetectchangeFeat();
};
