#include "siteOps.h"

void siteOps::removeShit(){
    rapidcsv::Document doc(path);
    bool isSiteFound = false;
    std::vector<std::string> emailCols = doc.GetColumn<std::string>(0);
    std::vector<std::string> siteCols = doc.GetColumn<std::string>(1);
    
    auto it = std::find(emailCols.begin(), emailCols.end(), email);
    auto it2 = std::find(siteCols.begin(), siteCols.end(), link);

    if(it != emailCols.end() && it2 != siteCols.end()){
        isSiteFound = true;
        int index = std::distance(emailCols.begin(), it);
        //doc.RemoveRow(index);
        //doc.Save();
    }

    if(isSiteFound){
        std::cout << "Successfully Removed " << link << " from " << email << "\n";
    } else {
        std::cout << "The Specified Site could not found :(\n";
    }
}