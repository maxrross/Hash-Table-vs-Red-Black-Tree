#include "HashTable.h"

HashTable::HashTable() {
    numBuckets = 1000;
    numEntries = 0;
    hTable = new std::vector<Person>[numBuckets];
    loadFactor = (float) numEntries / (float) numBuckets;
}

void HashTable::UpdateLoad() {
    loadFactor = (float) numEntries / (float) numBuckets;
}

void HashTable::Insert(std::string fName, std::string lName, std::string address, std::string city, std::string state,
                       std::string zip, std::string phoneNum) {
    // check loadFactor, insert accordingly
    if (loadFactor < 0.8)
        hTable[Hash(fName, lName)].emplace_back(fName, lName, address, city, state, zip, phoneNum);
    else {
        ReHash();
        hTable[Hash(fName, lName)].emplace_back(fName, lName, address, city, state, zip, phoneNum);
    }

    numEntries++;
    UpdateLoad();
}

int HashTable::Hash(std::string fName, std::string lName) {
    // hash function based on https://cp-algorithms.com/string/string-hashing.html#search-for-duplicate-strings-in-an-array-of-strings
    int p = 29791;
    long long currentHash = 0;
    std::string toHash = fName + lName;

    for (int i = 0; i < toHash.length(); i++) {
        currentHash += (toHash[i] * (int)std::pow(p, i));
    }

    // if hash val overflows simply change to positive
    if (currentHash < 0)
        currentHash *= -1;

    return (int)(currentHash % numBuckets);
}

void HashTable::ReHash() {
    int oldBuckets = numBuckets;
    numBuckets *= 1.5;
    std::vector<Person>* temp = new std::vector<Person>[numBuckets];

    // copy each Person obj from current hTable to temp
    for (int i = 0; i < oldBuckets; i++) {
        for (int j = 0; j < hTable[i].size(); j++) {
            temp[Hash(hTable[i][j].fName, hTable[i][j].lName)].push_back(hTable[i][j]);
        }
    }

    // assign hTable to temp, and clear temp
    hTable = temp;
    temp->clear();

    UpdateLoad();
}

void HashTable::Search(std::string first, std::string last) {
    int index = Hash(first, last);
    int numMatches = 0;

    if (hTable[index].size() > 0) {
        for (int i = 0; i < hTable[index].size(); i++) {
            if (hTable[index][i].fName == first && hTable[index][i].lName == last)
                numMatches++;
        }

        if (numMatches == 0)
            std::cout << "No matches found." << std::endl;
        else {
            if (numMatches == 1)
                std::cout << numMatches << " Match found. Displaying." << std::endl;
            else
                std::cout << numMatches << " Matches found. Displaying all." << std::endl;

            for (auto & x : hTable[index]) {
                if (x.fName == first && x.lName == last)
                    x.Print();
            }
        }
    }
    else {
        std::cout << "No matches found." << std::endl;
    }
}

void HashTable::TimeTrial(int n) {
    int i = 0;

    auto start = std::chrono::high_resolution_clock::now();
    while (i < n) {
        if (hTable[i].size() == 0) {
            i++;
            continue;
        }
        else {
            for (int j = 0; j < hTable[i].size(); j++) {
                i++;
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Accessed the first " << n << " Hash Table elements sequentially in " << duration.count() << " microseconds" << std::endl;
}
