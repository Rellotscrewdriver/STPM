#include "dectargs.h"

void dectargs::checkArgs() {
  if(mArgc >= 2) {
    dectTypeArgs();
  } else if(mArgc == 1){
    helpMessage();
  } else {
    std::cout << "not enough parameters or too many parameters"
              << "\nparamter count: " << mArgc << std::endl;
  }
}

void dectargs::dectTypeArgs() {
  if((funcNameCmp("add") || funcNameCmp("Add")) && mArgc > 2) {
    addPassSite *aps = new addPassSite(mArgVect[2], mArgVect[3]); 
    delete aps;
  } else if (funcNameCmp("list") || funcNameCmp("List") && mArgc > 2) {
    std::cout << "List Function here";
  } else if (funcNameCmp("change") || funcNameCmp("Change") && mArgc > 2) {
    std::cout << "Change Function here";
  } else if (funcNameCmp("remove") || funcNameCmp("Remove") && mArgc > 2) {
    removeSite *rs = new removeSite(mArgVect[2]);
    delete rs;
  } else {
    std::cout << "Not FOUND";
  }
}

bool dectargs::funcNameCmp(std::string funcName){
  //converts char* to string, this is not done by default, stupid C devs
  tempVal = mArgVect[1];
  return (tempVal == funcName);
}

void dectargs::helpMessage(){
  std::cout << "Help Section Here \nThis software is in early development :)";
}
