#include <iostream>
using namespace std;

class Window
{
    private:
        int size;
    public:

        Window(int size) : size(size)
        {}

        virtual void onResize()
        {
            size += 30;
            cout << "Resize the window " << size <<endl;
            return;
        }

        void resize()
        {
            size += 40;
        }

        int getSize()
        {
            return size;
        }
};

class SpecialWindow : public Window
{
    public:

        SpecialWindow(int size) : Window(size)
        {}

        virtual void onResize()
        {
            static_cast<Window>(*this).onResize();
            Window::onResize();
            resize();

            cout << "Resize the specialwindow " << getSize() << endl;

        }
};

void doSomeResize(Window& w)
{
    w.onResize();
}

int main()
{
    SpecialWindow a(10);
    a.onResize();

    doSomeResize(Window(10));
    doSomeResize(static_cast<Window>(10));
    
}