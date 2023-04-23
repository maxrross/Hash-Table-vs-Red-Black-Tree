#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include "HashTable.h"
#include "RedBlack.h"

void PrintAscii();
void InsertTable(std::string fileName, HashTable& table);
void InsertTree(std::string fileName, RedBlack& tree);
void HandleInstructions(HashTable& table, RedBlack& tree);

int main() {
    HashTable table;
    RedBlack tree;
    PrintAscii();
    InsertTable("data/data.txt", table);
    InsertTree("data/data.txt", tree);
    HandleInstructions(table, tree);

    return 0;
}

void PrintAscii() {
    // from https://patorjk.com/software/taag/#p=display&f=Doom&t=Ligma%20Productions
    std::cout << " _     _                        ______              _            _   _                 \n"
                 "| |   (_)                       | ___ \\            | |          | | (_)                \n"
                 "| |    _  __ _ _ __ ___   __ _  | |_/ / __ ___   __| |_   _  ___| |_ _  ___  _ __  ___ \n"
                 "| |   | |/ _` | '_ ` _ \\ / _` | |  __/ '__/ _ \\ / _` | | | |/ __| __| |/ _ \\| '_ \\/ __|\n"
                 "| |___| | (_| | | | | | | (_| | | |  | | | (_) | (_| | |_| | (__| |_| | (_) | | | \\__ \\\n"
                 "\\_____/_|\\__, |_| |_| |_|\\__,_| \\_|  |_|  \\___/ \\__,_|\\__,_|\\___|\\__|_|\\___/|_| |_|___/\n"
                 "          __/ |                                                                        \n"
                 "         |___/   \n\n\n" << std::endl;

    std::cout << "Initializing Data Structures \n" << std::endl;
}

void InsertTable(std::string fileName, HashTable& table) {
    std::ifstream inFile(fileName);
    std::string line;
    std::string word;
    std::vector<std::string> row;
    std::vector<Person> people;
    int num = 0;

    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(8);

    auto start = std::chrono::high_resolution_clock::now();

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            row.clear();
            std::stringstream s(line);

            while (std::getline(s, word, ',')) {
                row.push_back(word);
            }

            table.Insert(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            num++;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Inserted " << num << " elements into Hash Table in " << duration.count() << " microseconds" << std::endl;
}

void InsertTree(std::string fileName, RedBlack& tree) {
    std::ifstream inFile(fileName);
    std::string line;
    std::string word;
    std::vector<std::string> row;
    std::vector<Person> people;
    int num = 0;

    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(8);

    auto start = std::chrono::high_resolution_clock::now();

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            row.clear();
            std::stringstream s(line);

            while (std::getline(s, word, ',')) {
                row.push_back(word);
            }

            tree.Insert(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            num++;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Inserted " << num << " elements into Red-Black Tree in " << duration.count() << " microseconds" << std::endl;
}

void HandleInstructions(HashTable& table, RedBlack& tree) {
    std::vector<std::string> instructions;
    std::string line;
    std::string word;

    while (std::getline(std::cin, line)) {
        instructions.clear();

        if (line == "exit")
            break;

        std::stringstream s(line);
        while(std::getline(s, word, ' ')) {
            instructions.push_back(word);
        }

        if (instructions[0] == "search" && instructions[1] == "table") {
            table.Search(instructions[2], instructions[3]);
        }
        else if (instructions[0] == "search" && instructions[1] == "tree") {
            tree.Search(instructions[2], instructions[3]);
        }
        else {
            std::cout << "Invalid instruction sequence" << std::endl;
        }
    }
}