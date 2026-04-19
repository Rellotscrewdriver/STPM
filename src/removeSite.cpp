#include "removeSite.h"

void removeSite::finalRemoveIt(){
    rapidcsv::Document doc(path);
    bool isSiteFound = false;
    std::vector<std::string> emailCols = doc.GetColumn<std::string>(0);
    std::vector<std::string> siteCols = doc.GetColumn<std::string>(1);
    
    auto it = std::find(emailCols.begin(), emailCols.end(), eraseLineEmail);
    auto it2 = std::find(siteCols.begin(), siteCols.end(), eraseLineLink);

    if(it != emailCols.end() && it2 != siteCols.end()){
        isSiteFound = true;
        int index = std::distance(emailCols.begin(), it);
        doc.RemoveRow(index);
        doc.Save();
    }

    if(isSiteFound){
        std::cout << "Successfully Removed " << eraseLineLink << " from " << eraseLineEmail << "\n";
    } else {
        std::cout << "The Specified Site could not found :(\n";
    }
}