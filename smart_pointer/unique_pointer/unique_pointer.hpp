#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Car
{
public:
    Car(const std::string name, const float x, const float y);
    
    Car() = delete; // 기본 생성자 제거
    Car(const Car& carInput) = delete; // 복사 생성자 제거

    virtual ~Car() = default; // 소멸자 내용 없음

    void PrintName(void);
    void PrintPose(void);

    void AddPos(const Car* other);

private:
    std::string mName;

    float mX;
    float mY;
};