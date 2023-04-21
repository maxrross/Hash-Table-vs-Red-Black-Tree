#include <fstream>
#include <sstream>
#include <chrono>
#include "Person.h"
#include "HashTable.h"

void ParseFile(std::string fileName, HashTable& table);
// do smth to read command line instructions

int main() {
    HashTable table;
    ParseFile("data/data.txt", table);

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
