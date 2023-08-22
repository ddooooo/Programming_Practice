#include <iostream>

class Share
{
    public:
        Share(int a) : a(a) {}

        void shareInt(const Share& s) { a = s.a;}

    private:
        int a;
};

int main()
{
    Share a(20);
    Share b(10);


}