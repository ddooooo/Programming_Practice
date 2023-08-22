#include <iostream>
#include <memory>
#include <cstring>
#include <vector>
#include <span>
#include <ranges>

class A 
{
    public:
        std::shared_ptr<A> p;
};

class B
{
    public:
        std::weak_ptr<B> p;
};

class C
{
    private:
        int num=0;
        char* str = nullptr;

    public:
        C() 
        {
            std::cout << "Default Constructor" << std::endl;
        }

        C(const char* s, int n=99) : num(n), str(new char[strlen(s)+1])
        {
            strcpy(str, s);
            std::cout << "Conversion Constructor " << str <<  std::endl;
        }

        C(const C& c) : num(c.num), str(new char[strlen(c.str)+1]) 
        {
            std::cout << "Copy Constructor" << std::endl;
            strcpy(str, c.str); 
        }

        C(C&& c) : num(c.num), str(c.str)
        {
            std::cout << "Move Constructor" << std::endl;
            c.num = 0;
            c.str = nullptr;
        }

        C& operator=(const C& c)
        {
            std::cout << "Copy Assignment" << std::endl;
            if(this != &c)
            {
                delete [] str;
                num = c.num;
                str = new char[strlen(c.str)+1];
                strcpy(str, c.str);
            }
            return *this;
        }

        C& operator=(C&& c)
        {
            std::cout << "Move Assignment" << std::endl;
            if(this != &c)
            {
                delete [] str;
                num = c.num;
                str = c.str;
                c.num = 0; c.str = nullptr;
            }
            return *this;
        }

        ~C() 
        {
            std::cout << "Destructor" << std::endl;
            delete [] str;
        }
        
        C test() const
        {
            std::cout << "Test" << std::endl;
            C temp(*this);
            temp.num = 10;
            temp.str[0] = 't';
            std::cout << temp.str << std::endl;
            return temp;
        }

        const char* get()
        {
            return str;
        }
};

void work_on_data(std::vector<int>& v)
{
    v[0] = 99;
}

void writeData1(std::span<int> data)
{
    data[0] = 100;
}

void writeData2(std::ranges::view auto data)
{
    data[0]=101;
}

void writeData3(std::ranges::range auto&& data)
{
    data[0]=200;
}

void readData(std::span<const int> data)
{
    std::cout << "Reading the data : " << data[0] << std::endl;
    // data[0] = 10; error
}

int main()
{
    // Circular Dependency when using shared pointer
    std::shared_ptr<A> share1 = std::make_shared<A>();
    std::shared_ptr<A> share2 = std::make_shared<A>();
    
    share1->p = share2;
    share2->p = share1;

    // std::cout << "weak1: " << share1.use_count() << " weak2: " << share2.use_count() << std::endl;

    // Solution for Circular Dependency
    // - use weak pointer
    // - it does not own the pointer
    std::shared_ptr<B> weak1 = std::make_shared<B>();
    std::shared_ptr<B> weak2 = std::make_shared<B>();

    weak1->p = weak2;
    weak2->p = weak1;

    // std::cout << "weak1: " << weak1.use_count() << " weak2: " << weak2.use_count() << std::endl;
    // std::cout << "weak1->p: " << weak1->p.use_count() << " weak2->p: " << weak2->p.use_count() << std::endl;
    
    // T&& 
    // - rvalue reference
    // - c++11의 기능으로 메모리를 효율적으로 사용할 수 있게 개발 
    // - temporary object의 홀드 가능할 수 있고 변경 가능하도록 개발
    // - temporary object 
    // - 스택에서 생성되고, out-of-scope어거나 프로그램이 종료될때 자동으로 소멸됨
    // - rvalue reference나 const reference로만 홀드 가능
    // int a = 8;
    // int&& b;
    // int&& c = a;

    // Move
    // - deep copy 생성자 대체로 이동(move) 생성자를 사용
    // - temporary object의 리소스를 복사하지 않고(copy constructor) 다른 객체에 옮김
    // - 메모리 효율성, 메모리 allocation이 필요하지 않음
    // - std::move(lvalue object) --> 그냥 static casting to rvalue reference of object
    C a("good", 1); // conversion constructor
    C b(a); // copy constructor
    C c("bad", 2); // conversion constructor
    b = c; // copy assignment

    // move assignment이 불려야 되지만, 
    // copy epilson, move epilson의 자동 최적화 때문에 이동생성자를 따로 부르지 않고 바로 생성
    std::cout << "move constructors and move assignments" << std::endl;
    C move1 = "move"; // 1. temp("move") -> conversion constructor, 2. move1 = temp -> move constructor


    // Owning and non-owning
    std::vector<int> v = {1, 2, 3, 4, 5};
    work_on_data(v);
    for(int i=0; i<v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    writeData1(v);
    readData(v);
    writeData2(std::views::all(v));
    readData(v);
    writeData3(v);
    readData(v);
}