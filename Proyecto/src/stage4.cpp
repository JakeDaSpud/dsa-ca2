#include "TreeMap.h"
#include <string>
#include <fstream>

int main(int argc, char const *argv[]);
bool valid_file_path(const std::string &file_path);
bool read_file(std::string &file_path, TreeMap<char, std::string> &treemap);
void menu(TreeMap<char, std::string> &treemap);

// Global Variables
std::string file_path;
bool tried_arg_file_path = false;
TreeMap<char, std::string> treemap;
BinaryTree<char> treemapSet;
struct data;
std::ostream& operator<<(std::ostream& os, const data d);

// These are going to be stored in a KVPair of type <std::string (name / primary key), data (other info)>
// Struct for Data Rows
struct data {
    // Name not stored in this struct, it is the key associated with this struct
    std::string platform;
    std::string genre;
    std::string publisher;
    int year;
};

std::ostream& operator<<(std::ostream& os, const data d) { 
    os << d.platform << ", "  << d.genre << ", "  << d.publisher << ", " << d.year << '\n';
    return os;
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
    
    menu(treemap);

    return 0;
}