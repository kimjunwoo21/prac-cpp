#include <iostream>
#include <string>
#include "unique_pointer.hpp"

Car::Car(const std::string name, const float x, const float y)
    : mName(name)
    , mX(x)
    , mY(y)
{
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

int main(void)
{
    // c++11
    // std::vector<std::unique_ptr<Car>*> carList;

    // carList.reserve(2);
    // carList.push_back(std::unique_ptr<Car>(new Car("first car")));
    // carList.push_back(std::unique_ptr<Car>(new Car("second car")));
    
    // carList.clear(); // call first and second car destructor that the Car class don't have. but it's okay.

    // 유니크 포인터를 위와 같은 방식으로 사용하면
    // 지웠던 메모리를 또 지우는 현상이 발생할 수 있음.
    // 
    // example
    // std::vector* vectorPtr = new std::vector();
    // std::unique_ptr<std::vector> firstVector(vectorPtr);
    // std::unique_ptr<std::vector> secondVector(vectorPtr);
    // secondVector = nullptr; // operator overloading

    // secondVector에 nullptr을 대입하면 유니크 포인터가 초기화 되면서 유니크 포인터가 가르켰던 메모리를 초기화.
    // 하지만 firstVector도 같은 메모리를 가르키고 있었으므로 후에 스코프를 벗어나며 firstVector도 초기화 될 때
    // 이미 지운 메모리를 또 지우게 됨.

    // 이러한 문제를 해결하기 위해 new 대신 std::make_unique 유틸리티 사용
    // 이 유틸리티를 사용하면 둘 이상의 유니크 포인터가 원시 포인터를 공유할 수 없게 막아줌
    
    // c++14
    std::vector<std::unique_ptr<Car>> carList;
    carList.reserve(3);

    // 유니크 포인터를 이용한 Car 객체 생성 후 carList vector에 삽입
    carList.push_back(std::make_unique<Car>("first car", 1.f, 2.f));
    carList.push_back(std::make_unique<Car>("second car", 3.f, 4.f));

    carList[0]->PrintPose();
    carList[1]->PrintPose();

    // reset 원시 포인터 메모리 제거
    carList[0] = nullptr; // or carList[0].reset()
    carList[0] = std::make_unique<Car>("third car", 5.f, 6.f);

    carList[0]->PrintPose();

    // 원시 포인터 가져오기
    std::unique_ptr<Car> fourthCar = std::make_unique<Car>("fourth car", 10.f, 12.f);
    carList[0]->AddPos(fourthCar.get());
    carList[0]->PrintPose();

    // 소유권을 포기
    std::unique_ptr<Car> fifthCar = std::make_unique<Car>("fifth car", 20.f, 22.f);
    Car* sixthCar = fifthCar.release();
    sixthCar->PrintPose();

    // 소유권 이전(stl 컨테이너에 유니크 포인터 요소를 추가하기 좋은 방법)
    // const 유니크 포인터는 이전 불가
    std::unique_ptr<Car> seventhCar = std::make_unique<Car>("seventh car", 30.f, 32.f);
    carList.push_back(std::move(seventhCar)); // 이전 개체 seventhCar는 모든 멤버를 포기하고 소유권을 넘김
    carList[2]->PrintPose();

    carList.clear();
    
    return 0;
}