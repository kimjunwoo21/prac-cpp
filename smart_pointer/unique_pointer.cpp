#include <iostream>
#include <string>
#include "unique_pointer.hpp"

Car::Car(std::string name)
    : mPos(new std::vector<float>())
    , mName(name)
{
    mPos->reserve(2); // the unique pointer mPos don't need destructor

    mPos->push_back(0.0f);
    mPos->push_back(0.0f);
}

void Car::Print(void)
{
    std::cout << mName << std::endl;
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
    carList.reserve(2);

    // 유니크 포인터를 이용한 Car 객체 생성 후 carList vector에 삽입
    carList.push_back(std::make_unique<Car>("first car"));
    carList.push_back(std::make_unique<Car>("second car"));

    carList[0]->Print();
    carList[1]->Print();

    // reset 원시 포인터 메모리 제거
    carList[0] = nullptr; // or carList[0].reset()
    carList[0] = std::make_unique<Car>("third car");

    carList[0]->Print();

    carList.clear();
    
    return 0;
}