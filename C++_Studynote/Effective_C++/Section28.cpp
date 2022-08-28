#include <iostream>

using namespace std;

class Point
{
    public:
        Point(int x, int y) : x(x), y(y) 
        {}

        void setX(int new_x)
        {
            x = new_x;
        }

        void setY(int new_y)
        {
            y = new_y;
        }

    private:
        int x;
        int y;
};

struct RectData
{
    Point ulhc;
    Point lrhc;
};

class Rectangle
{
    public:
        Rectangle(Point upper, Point lower) 
        {
            pData->ulhc = upper; 
            pData->lrhc = lower;
        }

        const Point& upperLeft() const {return pData->ulhc;}
        const Point& lowerRight() const {return pData->lrhc;}
    
    private:
        shared_ptr<RectData> pData;
};

int main()
{
    Point coord1(0, 0);
    Point coord2(100, 100);
    Rectangle rect(coord1, coord2);

    rect.lowerRight().setX(100); // Not good, it access to the private member 

    
}