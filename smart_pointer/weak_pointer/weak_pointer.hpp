#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Driver;

class Car
{
public:
    Car(const std::string name, const float x, const float y);
    
    Car() = delete; // 기본 생성자 제거
    Car(const Car& carInput) = delete; // 복사 생성자 제거

    virtual ~Car();

    void PrintName(void);
    void PrintPose(void);

    void RegisterDriver(std::shared_ptr<Driver> ptr);

    void AddPos(const Car* other);

private:
    std::string mName;

    float mX;
    float mY;

    std::shared_ptr<Driver> driver;
};

class Driver
{
public:
    Driver(const std::string name);

    Driver() = delete;
    Driver(const Driver& input) = delete;

    void BuyCar(std::weak_ptr<Car> ptr);

    virtual ~Driver();

private:
    std::string mName;
    std::weak_ptr<Car> myCar;
};