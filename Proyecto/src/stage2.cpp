#include "TreeMap.h"
#include <string>
#include <fstream>

int main(int argc, char const *argv[]);
bool valid_char(char c);
bool read_file(const std::string &file_path, TreeMap<char, std::string> &treemap);
void menu(TreeMap<char, std::string> &treemap);

// Global Variables
std::string file_path;
bool tried_arg_file_path = false;
TreeMap<char, std::string> treemap;
BinaryTree<char> treemapSet;

int main(int argc, char const *argv[])
{

    do {
        // If there's something passed after the app, assume that's the file path location
        if (argc > 1 && !tried_arg_file_path) {
            file_path = argv[1];
        }

        // Otherwise: ask in app
        else {
            std::cout << "\nEnter your file name inside of the /data folder: ";
            std::cin >> file_path;
            // Making sure the file is a .txt
            if (file_path.length() < 5 || file_path.substr(file_path.length()-4) != ".txt") { file_path += ".txt"; }
            file_path = ".\\data\\" + file_path;
        }

        std::cout << file_path + "\n";

    } while (!read_file(file_path, treemap));
    
    menu(treemap);

    return 0;
}

bool valid_char(char c) {
    if ((c > 64 && c < 91) || // uppercase ASCII english alphabet
        (c > 96 && c < 123) || // lowercase ASCII english alphabet
        (c == ' ' || c == '\n')) {
            return true;
    }

    return false;
}

bool read_file(const std::string &file_path, TreeMap<char, std::string> &treemap) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open the file at " << file_path << '\n';
        tried_arg_file_path = true;
        return false;
    }

    // Parse file: Add all items to TreeMap<KVPair<char FIRST LETTER OF WORD, std::string WORD>>

    std::string word;
    char current;

    // Go through char by char
    while (file.get(current)) {
        // all chars have to be uppercase, so if not in english alphabet ranges of ASCII (uppercase = 65-90 and lowercase = 97-122), we ignore
        if (!valid_char(current)) {
            continue;
        }

        // if '\n' or ' ' -> we need to add the previously-made word into the treemap
        if (word != "" && (current == ' ' || current == '\n')) {

            // New to the map
            if (!treemap.containsKey(word[0])) {
                treemap.put(word[0], word);
            }

            // Already in the map, update the string
            else {
                treemap.put(word[0], treemap.get(word[0]) + '_' + word);
            }

            word = ""; // Reset word
        }

        // make uppercase and add to word
        else {
            word += toupper(current);
        }
    }

    // The last word might not be "finalised" if there is no '\n' or ' ' by the eof
    // So we have to add the last one (providing it's not empty!)
    if (word != "") {
        if (!treemap.containsKey(word[0])) {
            treemap.put(word[0], word);
        } else {
            treemap.put(word[0], treemap.get(word[0]) + '_' + word);
        }
    }

    file.close();

    // All words added, file parsed, make the keySet
    treemapSet = treemap.keySet();

    return true;
}

void menu(TreeMap<char, std::string> &treemap) {
    char userInput;
    char sentinel = '0';

    do {
        std::cout <<
        "\nMenu\n" <<
        "1. List letters with words\n" <<
        "2. View words for a certain letter\n" <<
        "0. Exit\n" <<
        "Enter: ";
        std::cin >> userInput;

        switch (userInput) {
        case '1':
            std::cout << "\n[1] Listing all letters that have at least 1 word:\n";
            // print treemapSet
            break;

        case '2':
            std::cout << "\n[2] Choose one of the following letters to view the words for:\n" ;
            // print treemapSet
            std::cout << "Enter: ";
            std::cin >> userInput;
            // if treemapSet.get(userInput) -> print all words
            // else "userInput char doesn't have any words"
            break;

        case '0':
            // End app, break loop
            break;
        
        default:
            std::cout << "\nUnrecognised command!";
            break;
        }

    } while (userInput != sentinel);

    std::cout << "\nGoodbye! :D\n";
}
