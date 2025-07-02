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
  if(strcmp(mArgVect[1], "add") == 0) {
    std::cout << "Stuff added\n";
  } else if (strcmp(mArgVect[1], "list") == 0) {
    std::cout << "none";
  }
}