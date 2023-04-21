#ifndef HASHTABLE_PERSON_H
#define HASHTABLE_PERSON_H

#include <string>

class Person {
public:
    Person(std::string fName, std::string lName, std::string address, std::string city,
           std::string state, std::string zip, std::string phoneNum);

    std::string fName;
    std::string lName;
    std::string address;
    std::string city;
    std::string state;
    std::string zip;
    std::string phoneNum;
};


#endif //HASHTABLE_PERSON_H
