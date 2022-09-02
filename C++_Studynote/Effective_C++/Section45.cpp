#include <iostream>

class Top
{};

class Middle : public Top
{};

class Bottom : public Middle
{};

template <typename T>
class SmartPtr
{
    public:
        explicit SmartPtr(T* realPtr)
        {}

        // Even though generalized copy constructor is defined, the copy constructor need to be defined
        SmartPtr(const SmartPtr& other)
        {}

        // Member function template
        // Generalized copy constructor
        template <typename U>
        SmartPtr(const SmartPtr<U>& other) : realPtr(other.get())
        {}

        SmartPtr& operator=(const SmartPtr& other)
        {}

        template <typename Y>
        SmartPtr& operator=(const SmartPtr<Y>& other)
        {}

        T* getPtr() 
        {
            return realPtr;
        }

    private:
        T* realPtr;
};

int main()
{
    // SmartPtr<Top> and SmartPtr<Middle> are completely different class
    // Need to define a function that convert SmartPtr<Middle> to SmartPtr<Top>
    // But if there are infinitely many inheritance class, defining such class will be tricky
    // Solution for such problem is Member function template
    SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle);
}