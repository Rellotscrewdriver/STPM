#include "dectargs.h"
#include "../Encryption/encryption.h"

using namespace std;

#if defined(_WIN32)
    // Windows path
    const std::string makeDir = ((localAppDir && localAppDir[0] != '\0') ? std::filesystem::path(localAppDir) / "STPM"
    : std::filesystem::path("C:\\STPM")).string();
#elif defined(__APPLE__)
    // macOS path
    const std::string makeDir = ((homeConfig && homeConfig[0] != '\0')
    ? std::filesystem::path(homeConfig) / "Library" / "Application Support" / "STPM"
    : std::filesystem::path(".") / "STPM").string();
#elif defined(__linux__)
    // Linux path, search in XDG_CONFIG_HOME first, then use HOME as fallback
    const std::string makeDir = 
    ((xdgEnv && xdgEnv[0] == '/')
      ? std::filesystem::path(xdgEnv) / "STPM"
      : (homeEnv && homeEnv[0] != '\0')
        ? std::filesystem::path(homeEnv) / ".config" / "STPM"
        : std::filesystem::path(".") / "STPM").string();
#else
    #error "Unsupported platform! you tryna compile in BSD or mobile or embedded?"
#endif


//TODO: make it so to restrict any commandline arguements when   
//TODO: create a new class to handle all these mess in main
namespace fs = std::filesystem;

bool createEmptyDirectory(const fs::path& dirPath) {
    std::error_code ec;

    // Creates the directory (and any missing parent paths)
    // If the directory already exists, it safely does nothing and returns false
    bool created = fs::create_directories(dirPath, ec);

    return true;
}

int main(int argc, char* argv[]) {
  // std::cout << "Inital: \n";
  // for(auto &i : siteDataNew){
  //   std::cout << "Data: " << i.getEmail() << " " << i.getLink() << " " << i.getPass() << "\n";
  // }
  fs::path myDir = makeDir;
  createEmptyDirectory(myDir);
  
  std::vector<std::string> argList(argv + 1, argv + argc);

  auto e = std::make_unique<encryption>();
  bool isTUI = (argc == 1);
  bool isDecrypted = true;
  if(!isTUI){
    isDecrypted = e->firstTimeUser();
  }
  

  // std::cout << "After encrypt decrypt: \n";
  // for(auto &i : siteDataNew){
  //   std::cout << "Data: " << i.getEmail() << " " << i.getLink() << " " << i.getPass() << "\n";
  // }

  if(!isDecrypted || argList.empty()){
    std::unique_ptr<dectargs> d = std::make_unique<dectargs>(argList);
  } else {
    std::cerr << "can't accept arguements if you are the new user \n";
  }

  if(!isDecrypted && !isTUI){
    e->encrypt();
  }

  // std::cout << "Final: \n";
  // for(auto &i : siteDataNew){
  //   std::cout << "Data: " << i.getEmail() << " " << i.getLink() << " " << i.getPass() << "\n";
  // }
}
