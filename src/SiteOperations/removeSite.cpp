#include "siteOps.h"

void siteOps::removeShit(){
    bool isSiteFound = false;
    for (auto it = siteData.begin(); it != siteData.end(); it++) {
        if (*it == email && *it == link) {
            // erase() returns the iterator to the next valid element
            it = siteData.erase(it);
            isSiteFound = true;
            break;
        }
    }

    if(isSiteFound){
        std::cout << "Successfully Removed " << link << " from " << email << "\n";
    } else {
        std::cout << "The Specified Site could not found :(\n";
    }
}