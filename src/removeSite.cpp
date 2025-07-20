#include "removeSite.h"

#include <iostream>
#include <fstream>
    

void removeSite::finalRemoveIt(std::string path, char* eraseLine){
    std::ifstream fin;
    std::ofstream temp;

    std::string eraseLineLink = link;
    std::string eraseLineEmail = email;

    fin.open(path);
    temp.open("temp.txt");

    if (fin.is_open()) {
        while (getline(fin, line)) {
            int pos = line.find(eraseLineLink);
            int pos1 = line.find(eraseLineEmail);
            if(pos == -1 || pos1 == -1){
                temp << line << endl;
            }/* could be useful in future if I wanna restore the passwords
                else {
                if (line != eraseLineLink) {
                    temp << line << endl;
                }
            }*/
        }
    } else {
        std::cout << "The File is not open!" << endl;
    }
 
    temp.close();
    fin.close();
    rename("temp.txt", path.c_str());

}