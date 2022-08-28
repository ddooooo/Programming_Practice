#include <iostream>
#include <string>

using namespace std;

class A
{    
    public:
        A() : text(0), a(0), c_m(20), cs_m(30) // 항상 멤버들을 초기화 해줘야 됨
        {
            b = 10; // 대입(assignment)이지 초기화(initialization)가 아님
        }

        const char& operator[] (size_t position) const
        {
            this->a = 10; // const function, 상수 함수는 *this pointer 도 상수 --> const A* this (pointer to const);
            return text[position];
        }

        char& operator[] (size_t position)
        {
            return const_cast<char&>(static_cast<const A&>(*this)[position]);
            //return text[position];
        }

    private:
        string text; // string 타입의 멤버는 empty string으로 초기화 됨
        int a; // 기본타입의 멤버는 초기화가 되지 않음..
        int b;
        const int c_m = 10;
        const static int cs_m = 20;
};