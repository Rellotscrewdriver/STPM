#include "siteOps.h"

void siteOps::removeShit(){
    bool isSiteFound = false;

    siteDataNew.erase(
        std::remove_if(siteDataNew.begin(), siteDataNew.end(), [this, &isSiteFound](siteObj& obj) {
            bool compare = (obj.getEmail() == this->email) && (obj.getLink() == this->link);
            if(compare){
                isSiteFound = true;
            }
            return compare; 
        }), 
        siteDataNew.end()
    );

    if(isSiteFound){
        std::cout << "Successfully Removed " << link << " from " << email << "\n";
    } else {
        std::cout << "The Specified Site could not found :(\n";
    }
}