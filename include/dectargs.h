#ifndef DECTARGS_H
#define DECTARGS_H

#include <memory>
#include <iostream>

class dectargs {
public:
  dectargs(int& cArgs, char* argVect[]);
  ~dectargs();
};

#endif