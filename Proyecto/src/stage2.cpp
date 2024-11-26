#include "TreeMap.h"
#include <string>

int main(int argc, char const *argv[]);
void read_file(const std::string &file_path, TreeMap<char, std::string> &treemap);
void menu(TreeMap<char, std::string> &treemap);

// Global Variables
std::string file_path;
TreeMap<char, std::string> treemap;
BinaryTree<char> treemapSet;

int main(int argc, char const *argv[])
{
    
    // Check CLI args for file location, if argc > 1 then skip asking for file

    // Ask for file location or read first .txt file in a Proyecto/data/ directory

    // read_file();
    
    // menu();

    return 0;
}

void read_file(const std::string &file_path, TreeMap<char, std::string> &treemap) {
    // Parse file: Add all items to TreeMap<KVPair<char FIRST LETTER OF WORD, std::string WORD>>
}

void menu(TreeMap<char, std::string> &treemap) {
    char userInput;
    char sentinel = '0';

    do {
        std::cout <<
        "Menu\n" <<
        "1. List letters with words\n" <<
        "2. View words for a certain letter\n" <<
        "0. Exit\n" <<
        "Enter: ";
        std::cin >> userInput;

        switch (userInput) {
        case '1':
            std::cout << "[1] Listing all letters that have at least 1 word:\n";
            // print treemapSet
            break;

        case '2':
            std::cout << "[2] Choose one of the following letters to view the words for:\n" ;
            // print treemapSet
            std::cout << "Enter: ";
            std::cin >> userInput;
            // if treemapSet.get(userInput) -> print all words
            // else "userInput char doesn't have any words"
            break;
        
        default:
            std::cout << "Unrecognised command!";
            break;
        }

    } while (userInput != sentinel);

    std::cout << "Goodbye! :D\n";
}
