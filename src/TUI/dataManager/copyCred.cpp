#include "dataManager.h"
#include <cstdio>

void dataManager::copyCreds(copyData type, int selectedRow){
    if (selectedRow >= 0 && selectedRow < data.size()) {
        if(type == copyEmail){
            std::string text_to_copy = data[selectedRow].name;
            copyToClipBoard(text_to_copy);
            //copyShit();
            status_message = "✅ Copied Email: \"" + text_to_copy + "\" to clipboard!";
        } else if(type == copySite){
            std::string text_to_copy = data[selectedRow].role; // Copying the "Role" column
            //copyShit();
            copyToClipBoard(text_to_copy);
            status_message = "✅ Copied Link: \"" + text_to_copy + "\" to clipboard!";
        } else if(type == copyPass){
            std::string text_to_copy = data[selectedRow].id;
            //copyShit();
            copyToClipBoard(text_to_copy);
            status_message = "✅ Copied Password: *********** to clipboard!";
        }
    }    
}

void dataManager::copyToClipBoard(const std::string &info){
    bool success = clip::set_text(info);

#ifndef _WIN32
    FILE* pipe = popen("wl-copy", "w");
    if (pipe) {
        fwrite(info.c_str(), sizeof(char), info.length(), pipe);
        pclose(pipe);
    } else {
        std::cerr << "Failed to open wl-copy pipe." << std::endl;
    }
#endif

}

