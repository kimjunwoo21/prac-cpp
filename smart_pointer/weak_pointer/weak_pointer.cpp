#include <iostream>
#include "weak_pointer.hpp"

// weak 포인터는 참조 카운터 기반 메모리 기법에서 순환 참조의 문제를 해결할 수 있다.

Car::Car(const std::string name, const float x, const float y)
    : mName(name)
    , mX(x)
    , mY(y)
{
    std::cout << mName << " is constructed." << std::endl;
}

Car::~Car(void)
{
    std::cout << mName << " is destroyed." << std::endl;
}

void Car::PrintName(void)
{
    std::cout << mName << std::endl;
}

void Car::PrintPose(void)
{
    std::cout << mName << ": " << mX << ", " << mY << std::endl;
}

void Car::AddPos(const Car* other)
{
    mX += other->mX;
    mY += other->mY;
}

void Car::RegisterDriver(std::shared_ptr<Driver> ptr)
{
    if (ptr == nullptr)
    {
        std::cout << "input shared pointer is empty" << std::endl;
        return;
    }

    driver = ptr;
}

Driver::Driver(const std::string name)
: mName(name)
{
    std::cout << mName << " is constructed." << std::endl;
}

Driver::~Driver(void)
{
    std::cout << mName << " is destroyed." << std::endl;
}

void Driver::BuyCar(std::weak_ptr<Car> ptr)
{
    if (ptr.expired())
    {
        std::cout << "input weak pointer is empty" << std::endl;
        return;
    }

    myCar = ptr;
}

int main(void)
{
    {
        std::shared_ptr<Car> owner = std::make_shared<Car>("first car", 0.f, 0.f); // 강한 참조 +1
        std::weak_ptr<Car> weakOwner = owner;  
        // 위크 포인터가 first car 객제를 약한 참조 하고 있는데 강한 참조를 하고 있는
        // owner가 만일 소멸되면 first car 객체는 사라지게 되어 문제가 발생
        // 따라서 위크 포인터는 공유 포인터로 바꿔서 사용해야하며 이 방법은 아래와 같음

        std::shared_ptr<Car> lockedOwner = weakOwner.lock(); // 이 때, 강한참조는 2, 약한참조는 1
        // 위 표현을 다시 설명하면 나 이 자원 쓸건데 내가 쓰고 있는 동안 남이 지우지 못한다는 뜻

        // 공유 포인터가 존재하는지 확인하는 방법
        if (lockedOwner == nullptr)
        {
            // 만일 위크포인터로 가져온 공유 포인터가 널 포인터이면
            // 해당 자원이 지워진 것. 따라서 강한 참조가 0이고 약한 참조가 1인 상황이므로
            // 이것에 대응을 해야함.
        }

        // 공유 포인터가 존재하는지 확인하는 또 다른 방법
        if (weakOwner.expired())
        {
            // expired가 true이면 확실히 지워진 상태이므로 로직 처리해도 됨.
            // 만일 false일 때 사용하는 로직을 쓴다면 조건문을 처리하는 시점에는 강한 참조가 존재했다가
            // 내부 로직을 처리할 때 강한 참조가 0이되어 자원이 소멸될 가능성이 있음.
        }
    }

    { // 순환 참조
        std::shared_ptr<Driver> driver = std::make_shared<Driver>("jw");
        std::shared_ptr<Car> car = std::make_shared<Car>("first car", 0.f, 0.f);
        std::weak_ptr<Car> weakCar = car;

        driver->BuyCar(weakCar);
        car->RegisterDriver(driver);

        car = nullptr;

        // 위크 포인터는 shared ptr로 받아야 한다.
        // 위크 포인터를 사용할때는 또 shared ptr에 넣어서 써야한다.
    }
    return 0;
}