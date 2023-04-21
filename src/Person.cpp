#include "Person.h"

Person::Person(std::string fName, std::string lName, std::string address, std::string city, std::string state,
               std::string zip, std::string phoneNum) {
    this->fName = fName;
    this->lName = lName;
    this->address = address;
    this->city = city;
    this->state = state;
    this->zip = zip;
    this->phoneNum = phoneNum;
}

