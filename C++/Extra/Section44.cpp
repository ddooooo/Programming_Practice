#include <iostream>

using namespace std;

template<typename T>
class SquareMatrixBase
{
    protected:

        SquareMatrixBase(size_t n, T* pMat) : n(n), pMat(pMat)
        {}

        // Solution #1 for code  bloat: call the function in the base class, and the function will be instantiated one time
        // This solution is not complete, as SquareMatrixBase does not contain the actual matrix from derived class
        void invert(size_t n)
        {
            cout <<  "Base class invert with " << n << endl; 
        }

        // Dangerous solution for code bloat
        void invert(SquareMatrixBase& smb)
        {
            cout << "Dangerous solution for code bloat " << endl;
        }

    private:
        size_t n;
        T* pMat;
};

template<typename T, size_t n>
class SquareMatrix : private SquareMatrixBase<T> // Implemenation inheritance 
{
    private:
        using SqaureMatrixBase<T>::invert;

    public:

        SquareMatrix() : SqaureMatrixBase(n, matrix)
        {}

        void invert()
        {
            this->invert(n); // will call invert(size_t) in base class
            this->invert(*this); // dangerous solution: the derived class won't be instantiated until the base class instantiated
        }

    private:
        T matrix[n*n]; // The memory for the pointer to matrix will be wasting, as the actual pointer to matrix is in base class
};

int main()
{
    // Code Bloat
    // SquareMatrix<double, 5>::invert and SquareMatrix<doube, 10>:: invert will be called
    // Even though invert() will do the same job regardless of size_t, it is instantiated twice for sm1 and sm2
    // Soluition is create a new class with only implementation function(invert()), and apply private inheritance
    SquareMatrix<double, 5> sm1;
    sm1.invert();
    SquareMatrix<double, 10> sm2;
    sm2.invert(); 

    //scoped_array<int> pDatat;

    // Another reason for code bloat
    // int, long have same binary expression 
    // vector<int> and vector<long> can be code bloat
    // pointer type also share same binary expression
    // list<int*> list<const int*> list<Squarematrix<int, 3>*> must share the same member function
    

}