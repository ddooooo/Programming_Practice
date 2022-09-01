#include <iostream>

using namespace std;

class Widget
{
    public:
        Widget();
        virtual ~Widget();

        virtual size_t size() const;
        virtual void normalize();
        void swap(Widget& other);
};

class NastyWidget : public Widget
{
    public:
        NastyWidget();
        virtual ~NastyWidget();

        virtual size_t size() const;
        virtual void normalize();
};

bool operator!=(Widget& w1, Widget& w2)
{
    if(w1.size() != w2.size())
    {
        return true;
    }
    
    return false;
}

void doProcessing(Widget& w)
{
    NastyWidget nw;
    if(w.size() > 10 && w != nw)
    {
        Widget temp(w);
        temp.normalize();
        temp.swap(nw);
    }
}

template<typename T>
void doProcessing(Tt& w)
{
    
}
