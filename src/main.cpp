#include "dectargs.h"
using namespace std;

int main(int argc, char* argv[]) {
  std::unique_ptr<dectargs> d = std::make_unique<dectargs>(argc, argv);
}