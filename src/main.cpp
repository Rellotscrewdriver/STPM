#include "dectargs.h"
#include "encryption.h"

using namespace std;

//TODO: make it so to restrict any commandline arguements when   
//TODO: create a new class to handle all these mess in main

int main(int argc, char* argv[]) {
  // std::cout << "Inital: \n";
  // for(auto &i : siteDataNew){
  //   std::cout << "Data: " << i.getEmail() << " " << i.getLink() << " " << i.getPass() << "\n";
  // }
  std::vector<std::string> argList(argv + 1, argv + argc);

  auto e = std::make_unique<encryption>();
  bool isDecrypted = e->firstTimeUser();
  // std::cout << "After encrypt decrypt: \n";
  // for(auto &i : siteDataNew){
  //   std::cout << "Data: " << i.getEmail() << " " << i.getLink() << " " << i.getPass() << "\n";
  // }
  // std::ofstream outFile(path);
  // outFile.close();

  if(!isDecrypted && !argList.empty()){
    std::unique_ptr<dectargs> d = std::make_unique<dectargs>(argList);
  } else {
    std::cerr << "can't accept arguements if you are the new user \n";
  }

  // std::vector<std::string> o1 = {"add", "meow@gmail.com", "FH4.com"};
  // dectargs d1(o1);
  // std::vector<std::string> o2 = {"add", "meow@gmail.com", "FH5.com"};
  // dectargs d2(o2);  
  // std::vector<std::string> o3 = {"add", "meow@gmail.com", "FH6.com"};
  // dectargs d3(o3);

  if(!isDecrypted){
    e->encryptRAM();
  }

  // std::cout << "Final: \n";
  // for(auto &i : siteDataNew){
  //   std::cout << "Data: " << i.getEmail() << " " << i.getLink() << " " << i.getPass() << "\n";
  // }
}
