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
    numBuckets *= 2;
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

        if (numMatches == 1){
            std::cout << "Found " << numMatches << " match" << std::endl;
            std::cout << "First Name: " << hTable[index][0].fName << std::endl;
            std::cout << "Last Name: " << hTable[index][0].lName << std::endl;
            std::cout << "Address: " << hTable[index][0].address << std::endl;
            std::cout << "City: " << hTable[index][0].city << std::endl;
            std::cout << "State: " << hTable[index][0].state << std::endl;
            std::cout << "Zip: " << hTable[index][0].zip << std::endl;
            std::cout << "Phone Number: " << hTable[index][0].phoneNum << std::endl;
       } else
            std::cout << "Found " << numMatches << " matches" << std::endl;
            for (int i = 0; i < hTable[index].size(); i++) {
                std::cout << "First Name: " << hTable[index][i].fName << std::endl;
                std::cout << "Last Name: " << hTable[index][i].lName << std::endl;
                std::cout << "Address: " << hTable[index][i].address << std::endl;
                std::cout << "City: " << hTable[index][i].city << std::endl;
                std::cout << "State: " << hTable[index][i].state << std::endl;
                std::cout << "Zip: " << hTable[index][i].zip << std::endl;
                std::cout << "Phone Number: " << hTable[index][i].phoneNum << std::endl;
            }
    }
    else {
        std::cout << "Not found" << std::endl;
    }
}