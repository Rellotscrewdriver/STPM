#include "dectargs.h"
#include "encryption.h"

using namespace std;

int main(int argc, char* argv[]) {
  std::vector<std::string> argList(argv + 1, argv + argc);

  auto e = std::make_unique<encryption>();
  bool isDecrypted = e->firstTimeUser();  
  //std::unique_ptr<dectargs> d = std::make_unique<dectargs>(argList);

  if(!isDecrypted){
    e->encryptRAM();
  }

}
