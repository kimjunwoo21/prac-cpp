#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Car
{
public:
    Car(std::string name);

private:
    std::unique_ptr<std::vector<float> > mPos;
};