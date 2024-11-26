#include "TreeMap.h"
#include <string>
#include <fstream>

int main(int argc, char const *argv[]);
bool valid_char(char c);
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

bool valid_char(char c) {
    if ((c > 64 && c < 91) || // uppercase ASCII english alphabet
        (c > 96 && c < 123) || // lowercase ASCII english alphabet
        (c == ' ' || c == '\n')) {
            return true;
    }

    return false;
}

void read_file(const std::string &file_path, TreeMap<char, std::string> &treemap) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open the file at " << file_path << '\n';
        return;
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
