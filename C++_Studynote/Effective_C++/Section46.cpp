#include <iostream>

using namespace std;

template<typename T>
class Rational
{
    public:    
        Rational(const T& numerator = 0, const T& denominator = 1) : n(numerator), d(denominator)
        {}

        // Friend function in class template will be called, no longer function template, it is just function member in Rational Class
        // When Rational<int> is instantiated, then the function operator*() in Rational class will be declared automatically
        // Hence, implicit type conversion can be applied to the parameters
        friend const Rational operator*(const Rational& lhs, const Rational& rhs)
        {
            // When the function is declared, then it needs to be defined as well
            return Rational(lhs.numerator()*rhs.numerator(), lhs.denominator()*rhs.denominator());
            //return doMultiply(lhs, rhs);
        }

        const T numerator() const
        {
            return n;
        }

        const T denominator() const
        {
            return d;
        }

    private:
        T n;
        T d;        
};

template<typename T>
const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs)
{
    return Rational<T>(lhs.n*rhs.n, lhs.d*rhs.d);
}

// Solution #2
// Use helper friend function, instead of operator overloading function
template<typename T>
const Rational<T> doMultiply(const Rational<T>& lhs, const Rational<T>& rhs)
{
    return Rational<T>(lhs.numerator()*rhs.numerator(), lhs.denominator()*rhs.denominator());
}

int main()
{
    Rational<int> half(1, 2);

    // operator*(half, 2) --> const Rational<T>& lhs = half, (const Rational<T>& rhs = 2)
    // it will give an error because template argument deduction won't do the implicit type conversion for Function template
    // So, integer type '2' won't be converted to Rational type
    // Solution is to use friend function, as template argument deduction cannot be applied to function template, but can be applied to class template
    Rational<int> result = half*2; 
    cout << result.numerator() << " " << result.denominator() << endl;
}