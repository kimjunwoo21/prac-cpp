#include <iostream>
#include <string>
#include "unique_pointer.hpp"

Car::Car(std::string name)
    :mPos(new std::vector<float>())
{
    mPos->reserve(2); // the unique pointer mPos don't need destructor

    mPos->push_back(0.0f);
    mPos->push_back(0.0f);
    
    std::cout << name << std::endl;
}


int main(void)
{
    std::vector<std::unique_ptr<Car> > carList;

    carList.reserve(2);

    carList.push_back(std::unique_ptr<Car>(new Car("first car")));
    carList.push_back(std::unique_ptr<Car>(new Car("second car")));
    
    carList.clear(); // call first and second car destructor that the Car class don't have. but it's okay.

    return 0;
}