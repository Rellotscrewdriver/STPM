#include "removeSite.h"

#include <iostream>
#include <fstream>
    
void eraseFileLine(std::string path, std::string eraseLine) {
}

void removeSite::finalRemoveIt(std::string path, char* eraseLine){
    std::ifstream fin;
    std::ofstream temp;

    linkStr = eraseLine;

    fin.open(path);
    // contents of path must be copied to a temp file then
    // renamed back to the path file
    temp.open("temp.txt");


    //if (fin.is_open()) {
        while (getline(fin, line)) {
            int pos = line.find(linkStr);
            std::string id = line.substr(0, pos);
            if (line == id) {
                temp << line << endl;
            }
        }
    //}
 
    //remove empty lines
//if (!line.empty()) {
 //   temp << line << endl;
//}
    temp.close();
    fin.close();
    rename("temp.txt", path.c_str());
    // required conversion for remove and rename functions
    /*
    const char * p = path.c_str();
    remove(p);
    ;
    */
}