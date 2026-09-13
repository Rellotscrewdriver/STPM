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


int main(int argc, char* argv[]) {
  std::filesystem::path myDir = makeDir;
  std::filesystem::create_directories(myDir);

  std::vector<std::string> argList(argv + 1, argv + argc);

  encryption e;
  bool isTUI = (argc == 1);
  int miscCmdLength = 2;
  bool isMiscCmd = (argc == miscCmdLength) && (argList[0].length() == miscCmdLength);
  bool isNewUser = true;
  
  if(!isTUI && !isMiscCmd){
    isNewUser = e.firstTimeUser();
  }
  
  if(!isNewUser || argList.empty() || isMiscCmd){
    std::unique_ptr<dectargs> d = std::make_unique<dectargs>(argList);
  } else {
    std::cerr << "can't accept Commandline-arguements if you are the new user\nrun the same command again if you're adding stuff";
  }

  if(!isNewUser && !isTUI && !isMiscCmd){
    e.encrypt();
  }
}
