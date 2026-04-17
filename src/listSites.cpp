#include "listSite.h"


listSite::listSite(){
    std::ifstream file(path, std::ios::app);
    std::string line;
    /*
    std::string line;
    while (file >> line) {
        addLines.push_back(line);
    }
    std::erase(addLines, separator);
    */
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;

        // Step 2: Split the line by commas
        while (std::getline(ss, word, ':')) {
            
            // OPTIONAL: Basic cleanup
            // Remove leading spaces (handles "word1, word2")
            word.erase(0, word.find_first_not_of(" "));
            // Remove trailing spaces or carriage returns (\r)
            word.erase(word.find_last_not_of(" \r\n\t") + 1);

            if (!word.empty()) {
                addLines.push_back(word);
            }
        }
    }

    displayInANiceTable(addLines);
};

void listSite::displayInANiceTable(const std::vector<std::string>& all_lines, int columns){
    if (all_lines.empty()) {
        std::cout << "The file is empty." << std::endl;
        return;
    }

    // Calculating the maximum width needed for each column
    std::vector<size_t> col_widths(columns, 0);
    for (size_t i = 0; i < all_lines.size(); ++i) {
        int col_index = i % columns; // Determine which column this element belongs to
        col_widths[col_index] = std::max(col_widths[col_index], all_lines[i].length());
    }

    //sets the header
    std::cout << std::left 
    << std::setw(col_widths[0] + 2) << "Email Address" 
    << std::setw(col_widths[1] + 2) << "Site" 
    << std::setw(col_widths[2] + 2) << "Password" << "\n";
    
    // Print the table row by row
    for (size_t i = 0; i < all_lines.size(); i += columns) {
        for (int j = 0; j < columns; ++j) {
            // Check if the element exists for the current cell
            if (i + j < all_lines.size()) {
                // Add 2 for padding for each column width
                std::cout << std::left << std::setw(col_widths[j] + 2) << all_lines[i + j];
            }
        }
        std::cout << std::endl;
    }
}