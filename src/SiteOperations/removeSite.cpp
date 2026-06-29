#include "siteOps.h"

void siteOps::removeShit(){
    bool isSiteFound = false;

    siteDataNew.erase(
        std::remove_if(siteDataNew.begin(), siteDataNew.end(), [&isSiteFound](siteObj& obj, const siteOps& c) {
            bool compare = obj.getEmail() == c.email && obj.getLink() == c.link;
            if(compare){
                isSiteFound = true;
            }
            return compare; 
        }), 
        siteDataNew.end()
    );

    // for (auto it = siteData.begin(); it != siteData.end(); it++) {
    //     if (*it == email && *it == link) {
    //         // erase() returns the iterator to the next valid element
    //         it = siteData.erase(it);
    //         isSiteFound = true;
    //         break;
    //     }
    // }

    if(isSiteFound){
        std::cout << "Successfully Removed " << link << " from " << email << "\n";
    } else {
        std::cout << "The Specified Site could not found :(\n";
    }
}