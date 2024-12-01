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
void tablePrintHeaders(data* d, int indexField, int secondaryField);
void tablePrintSized(std::string &d, int indexField);
void tablePrintFullRow(data* d);
void updateUniqueValues(std::string &currentValue, std::string *uniqueValues, int &nextUniqueValueIndex, int *valueCounts);
void printIndexOnField(TreeMap<std::string, BinaryTree<data>> &treemap, const int &treemapSize, int fieldIndex);
void printDataWithValue(TreeMap<std::string, BinaryTree<data>> &treemap, std::string value, int fieldIndex);

// Global Variables
std::string file_path;
bool tried_arg_file_path = false;
TreeMap<std::string, BinaryTree<data>> treemap;
BinaryTree<std::string> treemapSet;
std::string dataHeaders[5] = {"Name", "Platform", "Genre", "Publisher", "Year"};
int dataLength[5] = {(int) dataHeaders[0].length(), (int) dataHeaders[1].length(), (int) dataHeaders[2].length(), (int) dataHeaders[3].length(), (int) dataHeaders[4].length()};

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
typedef struct data data; // Here so I don't have to write struct data everywhere, I can just write data

std::ostream& operator<<(std::ostream& os, const data d) { 
    os << d.platform << ", "  << d.genre << ", "  << d.publisher << ", " << d.year << '\n';
    return os;
}

std::string toupper(std::string &s) {
    std::string sCopy = s;

    for (int i = 0; i < s.length(); i++) {
        sCopy[i] = toupper(s[i]);
    }
    return sCopy;
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

    //std::cout << "DEBUG PRINT:\n";
    //treemap.keySet().printInOrder();
    
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

        // Check if these are longer than the max lengths already
        if (newData.name.length() > dataLength[0])
            dataLength[0] = newData.name.length();

        if (newData.platform.length() > dataLength[1])
            dataLength[1] = newData.platform.length();

        if (newData.genre.length() > dataLength[2])
            dataLength[2] = newData.genre.length();

        if (newData.publisher.length() > dataLength[3])
            dataLength[3] = newData.publisher.length();

        if (yearString.length() > dataLength[4])
            dataLength[4] = yearString.length();

        if (treemap.containsKey(newData.name)) {
            treemap.get(newData.name).add(newData);
        } else {
            BinaryTree<data> newTree;
            newTree.add(newData);
            treemap.put(newData.name, newTree);
        }

        //std::cout << "Added " << newDataCount << " rows\n";
    }

    std::cout << "Finished reading file\n";

    file.close();

    // All words added, file parsed, make the keySet
    treemapSet = treemap.keySet();

    return true;
}

void tablePrintHeaders(data* d, int indexField, int secondaryField) {
    std::string index(dataLength[indexField-1], ' ');
    std::string secondary(dataLength[secondaryField-1], ' ');

    std::string spacer = " | ";
    
    // Set indexField
    if (indexField == 1) {
        index = d->name;
    } else if (indexField == 2) {
        index = d->platform;
    } else if (indexField == 3) {
        index = d->genre;
    } else if (indexField == 4) {
        index = d->publisher;
    } else if (indexField == 5) {
        index = d->year;
    } else {
        std::cerr << "Invalid tablePrintHeaders() indexField!\n";
    }

    // Set secondaryField
    if (secondaryField == 1) {
        secondary = d->name;
    } else if (secondaryField == 2) {
        secondary = d->platform;
    } else if (secondaryField == 3) {
        secondary = d->genre;
    } else if (secondaryField == 4) {
        secondary = d->publisher;
    } else if (secondaryField == 5) {
        secondary = d->year;
    } else {
        std::cerr << "Invalid tablePrintHeaders() secondaryField!\n";
    }

    std::cout << index << spacer << secondary;
}

// Wow I can't believe I just came up with this beautiful padding solution
void tablePrintSized(std::string &d, int indexField) {
    int padCount = dataLength[indexField-1] - d.length();
    std::cout << d << std::string(padCount, ' ');
}

void tablePrintFullRow(data* d) {
    std::string name(dataLength[0], ' ');
    std::string platform(dataLength[1], ' ');
    std::string genre(dataLength[2], ' ');
    std::string publisher(dataLength[3], ' ');
    std::string year(dataLength[4], ' ');

    std::string spacer = " | ";

    for (int i = 0; i < d->name.length(); i++) {
        name[i] = d->name[i];
    }

    for (int i = 0; i < d->platform.length(); i++) {
        platform[i] = d->platform[i];
    }

    for (int i = 0; i < d->genre.length(); i++) {
        genre[i] = d->genre[i];
    }

    for (int i = 0; i < d->publisher.length(); i++) {
        publisher[i] = d->publisher[i];
    }

    for (int i = 0; i < std::to_string(d->year).length(); i++) {
        year[i] = std::to_string(d->year)[i];
    }

    std::cout << name << spacer << platform << spacer << genre << spacer << publisher << spacer << year << '\n';
}

void updateUniqueValues(std::string &currentValue, std::string *uniqueValues, int &nextUniqueValueIndex, int *valueCounts) {
    // Comparing with uniqueValues
    bool found = false;
    for (int j = 0; j < nextUniqueValueIndex; j++) {
        // Already in uniqueValues array
        if (currentValue == uniqueValues[j]) {
            found = true;
            valueCounts[j]++;
            break;
        }
    }

    // Not in uniqueValues array
    if (!found) {
        uniqueValues[nextUniqueValueIndex] = currentValue;
        valueCounts[nextUniqueValueIndex] = 1;
        nextUniqueValueIndex++;
    }
}

void printIndexOnField(TreeMap<std::string, BinaryTree<data>> &treemap, const int &treemapSize, int fieldIndex) {
    std::string *uniqueValues = new std::string[treemap.size()];
    int nextUniqueValueIndex = 0;
    int *valueCounts = new int[treemap.size()];
    std::string divider(dataLength[fieldIndex-1], '-');
    divider += "-|------\n";

    KVPair<std::string, BinaryTree<data>>* nodes = treemap.toArray();

    switch (fieldIndex) {
    case 1:
        for (int i = 0; i < treemap.size(); i++) {
            std::string currentValue = nodes[i].getValue().root->getItem().name;
            updateUniqueValues(currentValue, uniqueValues, nextUniqueValueIndex, valueCounts);
        }

        tablePrintSized(dataHeaders[0], 1);
        std::cout << " | Count\n";
        std::cout << divider;

        for (int i = 0; i < nextUniqueValueIndex; i++) {
            tablePrintSized(uniqueValues[i], 1);
            std::cout << " | " << valueCounts[i] << '\n';
        }
        break;

    case 2:
        for (int i = 0; i < treemap.size(); i++) {
            std::string currentValue = nodes[i].getValue().root->getItem().platform;
            updateUniqueValues(currentValue, uniqueValues, nextUniqueValueIndex, valueCounts);
        }

        tablePrintSized(dataHeaders[1], 2);
        std::cout << " | Count\n";
        std::cout << divider;

        for (int i = 0; i < nextUniqueValueIndex; i++) {
            tablePrintSized(uniqueValues[i], 2);
            std::cout << " | " << valueCounts[i] << '\n';
        }
        break;

    case 3:
        for (int i = 0; i < treemap.size(); i++) {
            std::string currentValue = nodes[i].getValue().root->getItem().genre;
            updateUniqueValues(currentValue, uniqueValues, nextUniqueValueIndex, valueCounts);
        }

        tablePrintSized(dataHeaders[2], 3);
        std::cout << " | Count\n";
        std::cout << divider;

        for (int i = 0; i < nextUniqueValueIndex; i++) {
            tablePrintSized(uniqueValues[i], 3);
            std::cout << " | " << valueCounts[i] << '\n';
        }
        break;

    case 4:
        for (int i = 0; i < treemap.size(); i++) {
            std::string currentValue = nodes[i].getValue().root->getItem().publisher;
            updateUniqueValues(currentValue, uniqueValues, nextUniqueValueIndex, valueCounts);
        }

        tablePrintSized(dataHeaders[3], 4);
        std::cout << " | Count\n";
        std::cout << divider;

        for (int i = 0; i < nextUniqueValueIndex; i++) {
            tablePrintSized(uniqueValues[i], 4);
            std::cout << " | " << valueCounts[i] << '\n';
        }
        break;

    case 5:
        for (int i = 0; i < treemap.size(); i++) {
            std::string currentValue = std::to_string(nodes[i].getValue().root->getItem().year);
            updateUniqueValues(currentValue, uniqueValues, nextUniqueValueIndex, valueCounts);
        }

        tablePrintSized(dataHeaders[4], 5);
        std::cout << " | Count\n";
        std::cout << divider;

        for (int i = 0; i < nextUniqueValueIndex; i++) {
            tablePrintSized(uniqueValues[i], 5);
            std::cout << " | " << valueCounts[i] << '\n';
        }
        break;
    
    default:
        std::cerr << "printIndexOnField: Unrecognised fieldIndex!\n";
        break;
    }

    delete[] uniqueValues;
    delete[] valueCounts;

    // Go through all nodes and data
    // Check if data.field is already in uniqueValues, if so, don't add, but incremement count
    // If not, add to uniqueValues and set increment count to 1
}

void printDataWithValue(TreeMap<std::string, BinaryTree<data>> &treemap, std::string value, int fieldIndex) {
    KVPair<std::string, BinaryTree<data>>* nodes = treemap.toArray();
    int valueInt;
    value = toupper(value);
    std::string spacer = "-|-";
    std::string divider(dataLength[0], '-');
    divider += spacer;
    divider += std::string(dataLength[1], '-');
    divider += spacer;
    divider += std::string(dataLength[2], '-');
    divider += spacer;
    divider += std::string(dataLength[3], '-');
    divider += spacer;
    divider += std::string(dataLength[4], '-');

    for (int i = 0; i < 5; i++) {
        tablePrintSized(dataHeaders[i], i+1);
        if (i != 4)
            std::cout << " | ";
    }

    std::cout << '\n' << divider << '\n';

    switch (fieldIndex) {
    case 1:
        // Compare name and string
        for (int i = 0; i < treemap.size(); i++) {
            if (toupper(nodes[i].getValue().root->getItem().name) == value) {
                tablePrintFullRow(nodes[i].getValue().toArray());
            }
        }
        break;
    
    case 2:
        // Compare name and string
        for (int i = 0; i < treemap.size(); i++) {
            if (toupper(nodes[i].getValue().root->getItem().platform) == value) {
                tablePrintFullRow(nodes[i].getValue().toArray());
            }
        }
        break;
        
    case 3:
        // Compare name and string
        for (int i = 0; i < treemap.size(); i++) {
            if (toupper(nodes[i].getValue().root->getItem().genre) == value) {
                tablePrintFullRow(nodes[i].getValue().toArray());
            }
        }
        break;
        
    case 4:
        // Compare name and string
        for (int i = 0; i < treemap.size(); i++) {
            if (toupper(nodes[i].getValue().root->getItem().publisher) == value) {
                tablePrintFullRow(nodes[i].getValue().toArray());
            }
        }
        break;

    case 5:
        valueInt = std::stoi(value);
        // Compare year and int
        for (int i = 0; i < treemap.size(); i++) {
            if (toupper(nodes[i].getValue().root->getItem().year) == valueInt) {
                tablePrintFullRow(nodes[i].getValue().toArray());
            }
        }
        break;

    default:
        std::cout << "Unrecognised fieldIndex!\n";
        break;
    }
}

void menu(TreeMap<std::string, BinaryTree<data>> &treemap) {
    std::string userInput;
    char sentinel = '0';

    do {
        std::cout <<
        "\nMenu\n" <<
        "1. Index a data field (View: Field of Choice, Count)\n" <<
        "2. View data with a specific value (In a specific Field of Choice)\n" <<
        "0. Exit\n" <<
        "Enter: ";
        std::getline(std::cin, userInput);

        // Make uppercase
        userInput = toupper(userInput);

        switch (userInput[0]) {
        case '1':
            std::cout << "\n[1] Choose one of the following fields to index for:\n" <<
            "1. " << dataHeaders[0] << '\n' <<
            "2. " << dataHeaders[1] << '\n' <<
            "3. " << dataHeaders[2] << '\n' <<
            "4. " << dataHeaders[3] << '\n' <<
            "5. " << dataHeaders[4] << '\n' <<
            "Enter: ";
            std::getline(std::cin, userInput);

            switch (userInput[0]) {
            case '1':
                std::cout << "\n[1] Indexing on " << dataHeaders[0] << ":\n";
                printIndexOnField(treemap, treemap.size(), 1);
                break;

            case '2':
                std::cout << "\n[1] Indexing on " << dataHeaders[1] << ":\n";
                printIndexOnField(treemap, treemap.size(), 2);
                break;

            case '3':
                std::cout << "\n[1] Indexing on " << dataHeaders[2] << ":\n";
                printIndexOnField(treemap, treemap.size(), 3);
                break;

            case '4':
                std::cout << "\n[1] Indexing on " << dataHeaders[3] << ":\n";
                printIndexOnField(treemap, treemap.size(), 4);
                break;

            case '5':
                std::cout << "\n[1] Indexing on " << dataHeaders[4] << ":\n";
                printIndexOnField(treemap, treemap.size(), 5);
                break;
            
            default:
                std::cout << "\nUnrecognised command!\n";
                break;
            }

            break;

        case '2':
            std::cout << "\n[2] Choose one of the following fields to search a specific value for:\n" <<
            "1. " << dataHeaders[0] << '\n' <<
            "2. " << dataHeaders[1] << '\n' <<
            "3. " << dataHeaders[2] << '\n' <<
            "4. " << dataHeaders[3] << '\n' <<
            "5. " << dataHeaders[4] << '\n' <<
            "Enter: ";
            std::getline(std::cin, userInput);

            int wantedFieldIndex;

            switch (userInput[0]) {
            case '1':
                std::cout << "\n[2] Enter a " << dataHeaders[0] << " to search for: ";
                std::getline(std::cin, userInput);
                printDataWithValue(treemap, userInput, 1);
                break;

            case '2':
                std::cout << "\n[2] Enter a " << dataHeaders[1] << " to search for: ";
                std::getline(std::cin, userInput);
                printDataWithValue(treemap, userInput, 2);
                break;

            case '3':
                std::cout << "\n[2] Enter a " << dataHeaders[2] << " to search for: ";
                std::getline(std::cin, userInput);
                printDataWithValue(treemap, userInput, 3);
                break;

            case '4':
                std::cout << "\n[2] Enter a " << dataHeaders[3] << " to search for: ";
                std::getline(std::cin, userInput);
                printDataWithValue(treemap, userInput, 4);
                break;

            case '5':
                std::cout << "\n[2] Enter a " << dataHeaders[4] << " to search for: ";
                std::getline(std::cin, userInput);
                printDataWithValue(treemap, userInput, 5);
                break;
            
            default:
                std::cout << "\nUnrecognised command!\n";
                break;
            }
            break;

        case '0':
            // End app, break loop
            break;
        
        default:
            std::cout << "\nUnrecognised command!\n";
            break;
        }

    } while (userInput[0] != sentinel);

    std::cout << "\nGoodbye! :D\n";
}
