#pragma once

#include "includes.h"

struct Record {
    std::string id;
    std::string name;
    std::string role;
};

class dataManager {
public:
    dataManager() = default;

    enum copyData {
        copyEmail,
        copySite,
        copyPass
    };

    std::string status_message = "nothing was copied to clipboard";
    std::string copyIns = "Use Arrows to navigate | Press 'c' to copy Name | Press 'v' to copy Role";

    std::vector<Record> data;
    std::vector<std::string> menu_entries;
    void updateMenuEnteries();

    void copyCreds(copyData type, int selectedRow);
    void addRow();
    void deleteRow(int selectedRow);
    void saveData();
};