#include "encryption.h"
#include "includes.h"

std::vector<std::string> encryption::convertToRawString(std::vector<siteObj> &sites){
    std::vector<std::string> temp;
    for(auto &i : sites){
        temp.push_back(i.getRawString());
    }
    rawStr = temp;
    return temp;
}

void encryption::convertToVectObj(){
    siteDataNew.reserve(rawStr.size()); // Optimization: Prevent multiple reallocations 

    for (const auto& item : rawStr) {
        std::stringstream ss(item);
        std::string segment;
        std::vector<std::string> parts;

        while (std::getline(ss, segment, ',')) {
            // Trim whitespace logic here using find_first_not_of/find_last_not_of 
            parts.push_back(segment);
        }

        // Construct object and add to vector
        // Using emplace_back to construct in-place and avoid copies 
        siteDataNew.push_back(siteObj(parts[0], parts[1], parts[2]));
    }
}