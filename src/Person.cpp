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

void Person::Print() const {
    std::cout << fName << " " << lName << ":" << std::endl;
    std::cout << "\t" << (char)(149) << " " << address << std::endl;
    std::cout << "\t" << (char)(149) << " " << city << std::endl;
    std::cout << "\t" << (char)(149) << " " << state << std::endl;
    std::cout << "\t" << (char)(149) << " " << zip << std::endl;
    std::cout << "\t" << (char)(149) << " " << phoneNum << std::endl;
    std::cout << "\n" << std::endl;
}




