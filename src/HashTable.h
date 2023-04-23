#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "Person.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>

class HashTable {
public:
    HashTable();
    void UpdateLoad();
    void Insert(std::string fName, std::string lName, std::string address, std::string city, std::string state,
                std::string zip, std::string phoneNum);
    int Hash(std::string fName, std::string lName);
    void ReHash();
    void Search(std::string first, std::string last);
    void TimeTrial(int n);

private:
    int numEntries;
    int numBuckets;
    float loadFactor;
    std::vector<Person>* hTable;
};


#endif //HASHTABLE_HASHTABLE_H
