#include "dectargs.h"

void dectargs::checkArgs() {
  std::cout << mArgc << std::endl;
  for(auto &i : mArgVect){
      std::cout << i << std::endl;
  }
  if(mArgc >= 1) {
    dectTypeArgs();
  } else if(mArgc == 0){
    helpMessage();
  } else {
    std::cout << "not enough parameters or too many parameters"
              << "\nparamter count: " << mArgc << std::endl;
  }
}

void dectargs::dectTypeArgs() {
  if((funcNameCmp("add") || funcNameCmp("Add")) && mArgc > 2) {
    siteOps site(mArgVect[1], mArgVect[2]);
    site.addSite();
  } else if (funcNameCmp("list") || funcNameCmp("List") && mArgc > 2) {
    // listSite *ls = new listSite();
    // delete ls;
  } else if (funcNameCmp("change") || funcNameCmp("Change") && mArgc > 2) {
    ArgNumberDetectchangeFeat();
  } else if (funcNameCmp("remove") || funcNameCmp("Remove") && mArgc > 2) {
    siteOps site(mArgVect[1], mArgVect[2]);
    site.removeSite();
    // removeSite *rs = new removeSite(mArgVect[2], mArgVect[3]);
    // delete rs;
  } else {
    std::cout << "Not FOUND";
  }
}

bool dectargs::funcNameCmp(std::string funcName){
  return (mArgVect[0] == funcName);
}

void dectargs::helpMessage(){
  std::cout << "Help Section Here \nThis software is in early development :)\n";
}

void dectargs::ArgNumberDetectchangeFeat(){
    if(mArgc == 5){
      // changeSite *cs = new changeSite(mArgVect[2], mArgVect[3], mArgVect[4]);
      // delete cs;
    } else {
      // changeSite *cs = new changeSite(mArgVect[2], mArgVect[3]);
      // delete cs;
    }
}