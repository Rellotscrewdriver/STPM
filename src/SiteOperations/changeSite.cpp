#include "siteOps.h"

void siteOps::regenPassword(){
    siteOps site(mFlag, mOldStr);
    site.removeSite();
    if(isSiteFound){
        site.addSite();
    }
}

void siteOps::replaceLink(){
    for (siteObj& s : siteDataNew) {
        if (s.getEmail() == mFlag && s.getLink() == mOldStr) {
            s.getLink() = mNewStr;
        }
    }
}

void siteOps::replaceEmail(){
    for (siteObj& s : siteDataNew) {
        if (s.getLink() == mFlag && s.getEmail() == mOldStr) {
            s.getEmail() = mNewStr;
        }
    }
}