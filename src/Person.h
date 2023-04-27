#ifndef HASHTABLE_PERSON_H
#define HASHTABLE_PERSON_H

#include <string>
#include <iostream>

class Person {
public:
    Person(std::string fName, std::string lName, std::string address, std::string city,
           std::string state, std::string zip, std::string phoneNum);
    void Print() const;

    // overload operators for comparing in tree insertion
    bool operator==(const Person& other) const {
        return (fName + lName) == (other.fName + other.lName);
    }

    bool operator<(const Person& other) const {
        return (fName + lName) < (other.fName + other.lName);
    }

    bool operator>(const Person& other) const {
        return (fName + lName) > (other.fName + other.lName);
    }

    bool operator!=(const Person& other) const {
        return (fName + lName) != (other.fName + other.lName);
    }
    
    std::string fName;
    std::string lName;
    std::string address;
    std::string city;
    std::string state;
    std::string zip;
    std::string phoneNum;
};


#endif //HASHTABLE_PERSON_H
