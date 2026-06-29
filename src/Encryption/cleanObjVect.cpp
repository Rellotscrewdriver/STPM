#include "encryption.h"
#include "includes.h"

void encryption::convertToRawString(){
    for(auto &i : siteDataNew){
        rawStr.push_back(i.getRawString());
    }
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
        siteDataNew.emplace_back(parts[0], parts[1], parts[2]);
    }

    std::cout << "Converted shit to objects\n";
    for(auto &i : siteDataNew){
        std::cout << i.getEmail() << "\n" << i.getLink() << "\n" << i.getPass() << "\n";
    }
}