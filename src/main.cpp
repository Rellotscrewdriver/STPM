#include "dectargs.h"
#include "encryption.h"

using namespace std;

int main(int argc, char* argv[]) {

  auto e = std::make_unique<encryption>();
  bool isDecrypted = e->firstTimeUser();  
  std::unique_ptr<dectargs> d = std::make_unique<dectargs>(argc, argv);
  
  if(!isDecrypted){
    e->encrypt();
  }

}
