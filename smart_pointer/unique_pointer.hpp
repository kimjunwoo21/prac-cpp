#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Car
{
public:
    Car(std::string name);
    
    virtual ~Car() = default;

    void Print(void);

private:
    std::unique_ptr<std::vector<float> > mPos;
    std::string mName;
};