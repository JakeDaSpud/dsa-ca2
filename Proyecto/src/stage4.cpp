#include "TreeMap.h"
#include <string>
#include <fstream>
#include <sstream>

struct data;
std::ostream& operator<<(std::ostream& os, const data d);

int main(int argc, char const *argv[]);
std::string toupper(std::string &s);
bool valid_file_path(const std::string &file_path);
bool read_file(std::string &file_path, TreeMap<std::string, BinaryTree<data>> &treemap);
void menu(TreeMap<std::string, BinaryTree<data>> &treemap);

// Global Variables
std::string file_path;
bool tried_arg_file_path = false;
TreeMap<std::string, BinaryTree<data>> treemap;
BinaryTree<std::string> treemapSet;
std::string dataHeaders[5] = {"Name", "Platform", "Genre", "Publisher", "Year"};
int dataLength[5] = {(int)dataHeaders[0].length(), (int)dataHeaders[1].length(), (int)dataHeaders[2].length(), (int)dataHeaders[3].length(), (int)dataHeaders[4].length()};

// These are going to be stored in a KVPair of type <std::string (name / primary key), data (other info)>
// Struct for Data Rows
struct data {
    std::string name;
    std::string platform;
    std::string genre;
    std::string publisher;
    int year;

    // Operators
    bool operator==(const data& other) const { return this->name == other.name; }
    bool operator<(const data& other) const { return this->name < other.name; }
    bool operator>(const data& other) const { return this->name > other.name; }
};
typedef struct data data; // Here so I don't have to write stuct data everywhere, I can just write data

std::ostream& operator<<(std::ostream& os, const data d) { 
    os << d.platform << ", "  << d.genre << ", "  << d.publisher << ", " << d.year << '\n';
    return os;
}

std::string toupper(std::string &s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}

bool valid_file_path(const std::string &file_path) {
    if (!file_path.empty() || 
        (file_path.length() < 5 && 
        (file_path.substr(file_path.length()-4) != ".csv") || file_path.substr(file_path.length()-4) != ".txt")
    ) {
        return true;
    }
    
    return false;
}

int main(int argc, char const *argv[]) {

    do {
        // If there's something passed after the app, assume that's the file path location
        if (argc > 1 && !tried_arg_file_path) {
            file_path = argv[1];
            tried_arg_file_path = true;
        }

        // Otherwise: ask in app
        else {
            std::cout << "\nEnter your file name inside of the /data folder: ";
            std::cin >> file_path;

            // Making sure the file is a .csv or .txt
            if (valid_file_path(file_path)) {
                file_path += ".csv";
            }
            file_path = ".\\data\\" + file_path;
        }

        std::cout << "Trying to open " << file_path + "\n";

    } while (!read_file(file_path, treemap));

    std::cout << "DEBUG PRINT:\n";
    treemap.keySet().printInOrder();
    
    menu(treemap);

    return 0;
}

bool read_file(std::string &file_path, TreeMap<std::string, BinaryTree<data>> &treemap) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open the file at " << file_path << '\n';
        return false;
    }

    std::cout << "Success\n";

    // Parsing file
    std::string row;
    std::string current;

    // Skip first Headers line
    getline(file, row);

    // Parsing .csv and creating all the BSTNode<data> nodes for the TreeMap's BinaryTree
    int newDataCount = 0;

    // In the data row
    while (std::getline(file, row)) {
        newDataCount++;

        // Geting each word in the row
        std::stringstream currentRow(row);
        std::string yearString; // Needs to be converted to int
        data newData;
    
        std::getline(currentRow, newData.name, ',');
        std::getline(currentRow, newData.platform, ',');
        std::getline(currentRow, newData.genre, ',');
        std::getline(currentRow, newData.publisher, ',');
        
        std::getline(currentRow, yearString, ',');
        newData.year = std::stoi(yearString);

        if (treemap.containsKey(newData.name)) {
            treemap.get(newData.name).add(newData);
        } else {
            BinaryTree<data> newTree;
            newTree.add(newData);
            treemap.put(newData.name, newTree);
        }

        std::cout << "Added " << newDataCount << " rows\n";
    }

    std::cout << "Finished reading file\n";

    file.close();

    // All words added, file parsed, make the keySet
    treemapSet = treemap.keySet();

    return true;
}

void menu(TreeMap<std::string, BinaryTree<data>> &treemap) {
    std::string userInput;
    char sentinel = '0';

    do {
        std::cout <<
        "\nMenu\n" <<
        "1. Index a data field (View: Name, Field of Choice)\n" <<
        "2. View data with a specific value (In a specific Field of Choice)\n" <<
        "0. Exit\n" <<
        "Enter: ";
        std::getline(std::cin, userInput);

        // Make uppercase
        userInput = toupper(userInput);

        switch (userInput[0]) {
        case '1':
            std::cout << "\n[1] Choose one of the following fields to index for:\n" <<
            "1. " << dataHeaders[1] << '\n' <<
            "2. " << dataHeaders[2] << '\n' <<
            "3. " << dataHeaders[3] << '\n' <<
            "4. " << dataHeaders[4] << '\n' <<
            "Enter: ";
            std::getline(std::cin, userInput);

            switch (userInput[0]) {
            case '1':
                std::cout << "\n[1] Indexing on " << dataHeaders[1] << ":\n";
                
                break;

            case '2':
                std::cout << "\n[1] Indexing on " << dataHeaders[2] << ":\n";

                break;

            case '3':
                std::cout << "\n[1] Indexing on " << dataHeaders[3] << ":\n";
            
                break;

            case '4':
                std::cout << "\n[1] Indexing on " << dataHeaders[4] << ":\n";

                break;
            
            default:
                std::cout << "\nUnrecognised command!\n";
                break;
            }

            break;

        case '2':
            std::cout << "\n[2] Choose one of the following letters to view the words for:\n" ;
            // print treemapSet
            treemapSet.printPreOrder();
            std::cout << "Enter: ";
            std::cin >> userInput;

            userInput = toupper(userInput);



            std::cout << '\n';
            break;

        case '0':
            // End app, break loop
            break;
        
        default:
            std::cout << "\nUnrecognised command!\n";
            break;
        }

    } while (userInput.length() != 1 && userInput[0] != sentinel);

    std::cout << "\nGoodbye! :D\n";
}
