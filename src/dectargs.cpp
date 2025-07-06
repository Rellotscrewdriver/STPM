#include "dectargs.h"

void dectargs::checkArgs() {
  if(mArgc <= 4) {
    dectTypeArgs();
  } else {
    std::cout << "not enough parameters or too many parameters"
              << "paramter count: " << mArgc << std::endl;
  }
}

void dectargs::dectTypeArgs() {
  if(funcNameCmp("add") || funcNameCmp("Add")) {
    addPassSite *aps = new addPassSite(mArgVect[2], mArgVect[3]); 
    delete aps;
  } else if (funcNameCmp("list") || funcNameCmp("List")) {
    std::cout << "none";
  }
}

bool dectargs::funcNameCmp(const char* funcName){
  return (strcmp(mArgVect[1], funcName) == 0);
}
