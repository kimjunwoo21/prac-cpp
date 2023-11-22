#include <iostream>
#include <string>
#include "unique_pointer.hpp"

Car::Car(std::string name)
    :mPos(new std::vector<float>())
{
    mPos->reserve(2); // the unique pointer mPos don't need destructor

    std::cout << name << std::endl;
}


int main(void)
{
    Car car("my car");
    
    return 0;
}