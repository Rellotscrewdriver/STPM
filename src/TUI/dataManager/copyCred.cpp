#include "dataManager.h"
#include <cstdio>

void dataManager::copyCreds(copyData type, int selectedRow){
    if (selectedRow >= 0 && selectedRow < siteDataNew.size()) {
        if(type == copyEmail){
            std::string text_to_copy = siteDataNew[selectedRow].getEmail();
            copyToClipBoard(text_to_copy);
            statusMessage = "✅ Copied Email: \"" + text_to_copy + "\" to clipboard!";
            text_to_copy.clear();
        } else if(type == copySite){
            std::string text_to_copy = siteDataNew[selectedRow].getLink();
            copyToClipBoard(text_to_copy);
            statusMessage = "✅ Copied Link: \"" + text_to_copy + "\" to clipboard!";
            text_to_copy.clear();
        } else if(type == copyPass){
            std::string text_to_copy = siteDataNew[selectedRow].getPass();
            copyToClipBoard(text_to_copy);
            statusMessage = "✅ Copied Password: *********** to clipboard!";
            text_to_copy.clear();
        }
    }    
}

void dataManager::copyToClipBoard(const std::string &info){
    #ifndef WIN32
        const char* waylandEnv = std::getenv("WAYLAND_DISPLAY");

        if(waylandEnv != nullptr){
            FILE* pipe = popen("wl-copy", "w");
            if (pipe) {
                fwrite(info.c_str(), sizeof(char), info.length(), pipe);
                pclose(pipe);
                return;
            }
        }
    #endif

    clip::set_text(info);
}

