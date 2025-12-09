#include "dectargs.h"
#include "encryption.h"
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

int main(int argc, char* argv[]) {
/*
  auto e = std::make_unique<encryption>();
  e->decrypt();
*/
  //std::unique_ptr<dectargs> d = std::make_unique<dectargs>(argc, argv);

  
  auto e = std::make_unique<encryption>();

  namespace fs = std::filesystem;
  auto sourceFilename = "add.txt";
  if (!fs::exists(sourceFilename) || fs::is_empty(sourceFilename)) {
    std::ofstream outFile(sourceFilename);
    e->encrypt();
  } else {
    e->decrypt();
  }
  
  std::unique_ptr<dectargs> d = std::make_unique<dectargs>(argc, argv);
  e->encrypt();
}