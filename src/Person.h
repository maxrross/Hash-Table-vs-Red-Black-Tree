#ifndef HASHTABLE_PERSON_H
#define HASHTABLE_PERSON_H

#include <string>

class Person {
public:
    Person(std::string fName, std::string lName, std::string address, std::string city,
           std::string state, std::string zip, std::string phoneNum);

    bool operator==(const Person& other) const {
        return (fName + lName) == (other.fName + other.lName);
    }

    bool operator<(const Person& other) const {
        if ((fName + lName) > (other.fName + other.lName)) {
            return (fName + lName) > (other.fName + other.lName);
        } else if ((fName + lName) < (other.fName + other.lName)) {
            return (fName + lName) < (other.fName + other.lName);
        } else {
            return zip < other.zip;
        }
    }

    bool operator>(const Person& other) const {
        if ((fName + lName) > (other.fName + other.lName)) {
            return (fName + lName) > (other.fName + other.lName);
        } else if ((fName + lName) < (other.fName + other.lName)) {
            return (fName + lName) < (other.fName + other.lName);
        } else {
            return zip > other.zip;
        }
    }

    bool operator!=(const Person& other) const {
        return (fName + lName) != (other.fName + other.lName);
    }

    bool operator<=(const Person& other) const {
        return (fName + lName) <= (other.fName + other.lName);
    }

    bool operator>=(const Person& other) const {
        return (fName + lName) >= (other.fName + other.lName);
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
