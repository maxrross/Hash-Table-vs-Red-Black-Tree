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
        hTable[Hash(fName)].emplace_back(fName, lName, address, city, state, zip, phoneNum);
    else {
        ReHash();
        hTable[Hash(fName)].emplace_back(fName, lName, address, city, state, zip, phoneNum);
    }

    numEntries++;
    UpdateLoad();
}

int HashTable::Hash(std::string fName) {
    // hash function based on https://cp-algorithms.com/string/string-hashing.html#search-for-duplicate-strings-in-an-array-of-strings
    int p = 29791;
    long long currentHash = 0;

    for (int i = 0; i < fName.length(); i++) {
        currentHash += (fName[i] * (int)std::pow(p, i));
    }

    // if hash val overflows simply change to positive
    if (currentHash < 0)
        currentHash *= -1;

    return (int)(currentHash % numBuckets);
}

void HashTable::ReHash() {
    std::vector<Person>* temp = new std::vector<Person>[numBuckets * 2];

    // copy each Person obj from current hTable to temp
    for (int i = 0; i < numBuckets; i++) {
        for (int j = 0; j < hTable[i].size(); j++) {
            temp[Hash(hTable[i][j].fName)].push_back(hTable[i][j]);
        }
    }

    // increase numBuckets, assign hTable to temp, and clear temp
    numBuckets *= 2;
    hTable = temp;
    temp->clear();

    UpdateLoad();
}

void HashTable::Search(std::string first, std::string last) {
    int index = Hash(first);

    if (hTable[index].size() > 0) {
        for (int i = 0; i < hTable[index].size(); i++) {
            if (hTable[index][i].lName == last)
                // do smth here
                std::cout << "Found" << std::endl;
        }
    }
    else {
        std::cout << "Not found" << std::endl;
    }
}