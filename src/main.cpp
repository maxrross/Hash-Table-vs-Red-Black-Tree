#include <fstream>
#include <sstream>
#include <chrono>
#include "Person.h"
#include "Person.cpp"
#include "HashTable.h"
#include "HashTable.cpp"
#include "RedBlack.cpp"

void ParseFile(std::string fileName, HashTable& table);
void HandleInstructions(HashTable& table);
/// add tree obj to function declaration so we can pass instructions to both

int main() {
    HashTable table;
    ParseFile("data.txt", table);
    HandleInstructions(table);

    RedBlack tree;
    ParseFile("data.txt", tree);
    tree.Search("Robert", "Wright");

    return 0;

    
}

void ParseFile(std::string fileName, HashTable& table) {
    std::ifstream inFile(fileName);
    std::string line;
    std::string word;
    std::vector<std::string> row;
    std::vector<Person> people;
    int num = 0;

    auto start = std::chrono::high_resolution_clock::now();

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            row.clear();
            std::stringstream s(line);

            while (std::getline(s, word, ',')) {
                row.push_back(word);
            }

            // insert into black red tree
            table.Insert(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            num++;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Inserted " << num << " elements in " << duration.count() << " microseconds" << std::endl;
}

void HandleInstructions(HashTable& table) {
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

        if (instructions[0] == "search") {
            table.Search(instructions[1], instructions[2]);
        }
        else {
            std::cout << "Invalid instruction sequence" << std::endl;
        }
    }
}