#include "dectargs.h"

dectargs::dectargs(int& cArgs, char* argVect[]) {
  for(int i = 1; i < cArgs; i++) {
    std::cout << argVect[i] << "\n";
  }
}

dectargs::~dectargs() {
}