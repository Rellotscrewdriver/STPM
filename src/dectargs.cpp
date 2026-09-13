#include "dectargs.h"
#include "TUI/tui.h"
#include "version.h"

dectargs::dectargs(std::vector<std::string> &vects) : mArgVect(vects) {
    mArgc = vects.size();
    checkArgs();
}

void dectargs::checkArgs() {
  if(mArgc >= 1 && mArgc <= 4) {
    dectTypeArgs();
  } else if(mArgc == 0){
    TUIFrontEnd ft;
    ft.exec();
  } else {
    std::cout << "too many parameters" << "\nparamter count: " << mArgc << std::endl;
  }
}

void dectargs::dectTypeArgs() {
  if((funcNameCmp("add") || funcNameCmp("Add")) && mArgc >= noOfArgsDetect) {
    siteOps site(mArgVect[1], mArgVect[2]);
    site.addSite();
  } else if ((funcNameCmp("list") || funcNameCmp("List")) && mArgc == 1) {
    siteOps site;
  } else if ((funcNameCmp("change") || funcNameCmp("Change")) && mArgc > noOfArgsDetect) {
    argNoChangeFeat();
  } else if ((funcNameCmp("remove") || funcNameCmp("Remove")) && mArgc > noOfArgsDetect) {
    siteOps site(mArgVect[1], mArgVect[2]);
    site.removeSite();
  } else if ((funcNameCmp("-h")) && mArgc == 1) {
    helpMessage();
  } else if ((funcNameCmp("-v")) && mArgc == 1) {
    versionString();
  } else {
    std::cout << "Main Arguement not found\n";
  }
}

bool dectargs::funcNameCmp(std::string funcName){
  return (mArgVect[0] == funcName);
}

void dectargs::helpMessage(){
  std::cout << "Usage: stpm [mode] <arg1> <arg2>\n" 
            << "\nShow this message: stpm -h\n"
            << "\nShow version: stpm -v\n"
            << "\nAdding Mode: stpm add <email> <link> \nadds the credential, the password will be automatically generated\nExample: stpm add RellotsHead@gmail.com github.com\n"
            << "\nRemoving Mode: stpm remove <email> <link> \nremoves a credential, errors out if not found\n"
            << "\nListing Mode: stpm list \nlists all credentials, prints everything in a nice table\n"
            << "\nChanging Mode: stpm change <flag> <oldCredential> <newCredential>\nupdates the credential\n"
            << "  Updating an email:     stpm change <link> <existingEmail> <newEmail>\n"
            << "  Updating a link:       stpm change <Email> <existingLink> <newLink>\n"
            << "  Regenerating Password: stpm change <Email> <Link>\n";
}

void dectargs::versionString(){
  std::cout << "STPM " << Version::STRING << "\n";
}

void dectargs::argNoChangeFeat(){
    if(mArgc == 4){
      siteOps site(mArgVect[1], mArgVect[2], mArgVect[3]);
      site.changeSite();
    } else {
      std::string Nothing = "";
      siteOps site(mArgVect[1], mArgVect[2], Nothing);
      site.changeSite();
    }
}