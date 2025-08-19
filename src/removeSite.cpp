#include "removeSite.h"

void removeSite::finalRemoveIt(){
    std::ifstream file;
    std::ofstream temp;
    file.open(path);
    temp.open("temp.txt");

    if (file.is_open()) {
        while (getline(file, line)) {
            posLink = line.find(eraseLineLink);
            posEmail = line.find(eraseLineEmail);
            if(posLink == -1 || posEmail == -1){
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
    std::cout << "Removed " << eraseLineLink << " from " << eraseLineEmail << "\n";
    temp.close();
    file.close();
    rename("temp.txt", path.c_str());
}