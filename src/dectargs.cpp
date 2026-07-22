#include "dectargs.h"
#include "tui.h"

void dectargs::checkArgs() {
  // std::cout << mArgc << std::endl;
  // for(auto &i : mArgVect){
  //     std::cout << i << std::endl;
  // }
  if(mArgc >= 1) {
    dectTypeArgs();
  } else if(mArgc == 0){
    TUIFrontEnd ft;
    ft.exec();
    //helpMessage();
    //This type of arguement should start the TUI session
  } else {
    std::cout << "not enough parameters or too many parameters"
              << "\nparamter count: " << mArgc << std::endl;
  }
}

// TODO: add an exception when mArgVect[n] are empty
void dectargs::dectTypeArgs() {
  if((funcNameCmp("add") || funcNameCmp("Add")) && mArgc > noOfArgsDetect) {
    siteOps site(mArgVect[1], mArgVect[2]);
    site.addSite();
  } else if ((funcNameCmp("list") || funcNameCmp("List")) && mArgc == 1) {
    siteOps site;
  } else if ((funcNameCmp("change") || funcNameCmp("Change")) && mArgc > noOfArgsDetect) {
    ArgNumberDetectchangeFeat();
  } else if ((funcNameCmp("remove") || funcNameCmp("Remove")) && mArgc > noOfArgsDetect) {
    siteOps site(mArgVect[1], mArgVect[2]);
    site.removeSite();
  } else {
    std::cout << "Not FOUND\n";
  }
}

bool dectargs::funcNameCmp(std::string funcName){
  return (mArgVect[0] == funcName);
}

void dectargs::helpMessage(){
  std::cout << "Help Section Here \nThis software is in early development :)\n";
}

void dectargs::ArgNumberDetectchangeFeat(){
    if(mArgc == 4){
      siteOps site(mArgVect[1], mArgVect[2], mArgVect[3]);
      site.changeSite();
    } else {
      std::string Nothing = "";
      siteOps site(mArgVect[1], mArgVect[2], Nothing);
      site.changeSite();
    }
}