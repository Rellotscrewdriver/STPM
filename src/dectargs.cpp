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
    std::cout << "Stuff added\n";
    std::cout << "Password is: " << pass->getgeneratedPass() << std::endl; 
  } else if (funcNameCmp("list") || funcNameCmp("List")) {
    std::cout << "none";
  }
}

bool dectargs::funcNameCmp(const char* funcName){
  return (strcmp(mArgVect[1], "add") == 0);
}

dectargs::~dectargs(){
  delete pass;
}