#include "dectargs.h"
#include "encryption.h"

using namespace std;

int main(int argc, char* argv[]) {
  std::vector<std::string> argList(argv + 1, argv + argc);

  auto e = std::make_unique<encryption>();
  bool isDecrypted = e->firstTimeUser();
  // std::cout << "After encrypt decrypt: \n";
  // for(auto &i : siteDataNew){
  //   std::cout << "Data: " << i.getEmail() << " " << i.getLink() << " " << i.getPass() << "\n";
  // }

  if(!isDecrypted || !argList.empty()){
    std::unique_ptr<dectargs> d = std::make_unique<dectargs>(argList);
  } else {
    std::cerr << "can't accept arguements if you are the new user \n";
  }

  if(!isDecrypted){
    e->encrypt();
  }

}
