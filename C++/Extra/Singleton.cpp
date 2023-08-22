#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>  

// Singleton (싱글톤) : 향상된 글로벌 변수값, 유니크한 인스턴스를 가진 객체, ex) 키보드, 디스플레이, 프린트매니저, 시스템시계
// 자동으로 생성되고 삭제되는 오브젝트
// Four types of Singleton
// 1. singleton following C++ rules - last created, first destroyed
// 2. Phoenix singleton - 삭제된 싱글톤 객체가 다른 객체가 필요로 할때 다시 생성 - OnDeadReference
// 3. singleton with longevity - 각 싱글톤 객체가 언제 삭제되는지 직접 결정
// 4. leaking singleton - 싱글톤의 리소스를 프로그램이 끝날때까지 삭제하지 않고 유지, '누수'
// SingletonHolder로 싱글톤 타입을 결정
class Singleton1
{
    public:
        static Singleton1* Instance()
        {
            if(!pInstance) pInstance=new Singleton1;
            return pInstance;
        }

    private: // 싱글톤의 유니크함을 유지하기 유해 private으로
        Singleton1();
        Singleton1(const Singleton1&); // 
        static Singleton1* pInstance;
};

class Singleton2
{
    public:
        static Singleton2& getInstance()
        {
            extern void __ConstructSingleton(void* memory);
            extern void __DestorySingleton();
            static bool __initialized = false;
            static char __buffer[sizeof(Singleton2)];
            if(!__initialized)
            {
                __ConstructSingleton(__buffer);
                atexit(__DestorySingleton); // atexit function - 프로그램이 끝날때, 등록된 함수들을 자동으로 불러줌, LIFO 순서로
                __initialized = true;
            }
            return *reinterpret_cast<Singleton2*>(__buffer);
        }
  
    private:
        Singleton2();
        Singleton2(const Singleton2&);
        Singleton2& operator=(const Singleton2&);
        static Singleton2* pInstance;
        ~Singleton2();
};

class BadSingleton
{
    public:
        static BadSingleton* Instance()
        {
            return &instance;
        }
    private:
        static BadSingleton instance; // dynamically initialization --> when the class is created, this static member is also created at that time
};

class Singleton
{
    private:
        //Data
        static Singleton* pInstance;
        static bool destroyed;
        Singleton() {}
        Singleton(const Singleton&);
        Singleton& operator=(const Singleton&);
        virtual ~Singleton()
        {
            std::cout << "Destory singleton" << std::endl;
            pInstance = 0;
            destroyed = true;
        }

        static void Create()
        {
            std::cout << "Create singleton for the first time!" << std::endl;
            static Singleton instance;
            pInstance = &instance;
        }
        
        static void OnDeadReference()
        {
            // throw std::runtime_error("Dead Reference Detected");
            Create();
            new(pInstance) Singleton;

            #ifdef ATEXIT_FIXED
                atexit(KillPhoenixSingleton);
            #endif
            
            destroyed = false;
        }
        
        static void KillPhoenixSingleton()
        {
            pInstance->~Singleton();
        }
        
    public:
        Singleton& getInstance()
        {
            std::cout << "Singleton get instance!" << std::endl;
            if(!pInstance)
            {   
                if(destroyed)
                {
                    OnDeadReference();
                } 
                else
                {
                    Create();
                }
            }
            return *pInstance;
        }
};

Singleton* Singleton::pInstance = 0;
bool Singleton::destroyed = false;

// Longetivity - 싱글톤의 삭제 순서를 관리하는 방법
namespace Private
{
    class LifetimeTracker
    {
        private:
            unsigned int longevity;
        public:
            LifetimeTracker(unsigned int x) : longevity(x) {}
            virtual ~LifetimeTracker() = 0;
            friend inline bool Compare(unsigned int longevity, const LifetimeTracker*p)
            {
                return p->longevity < longevity;
            }
    };

    bool Check(int a, const int b)
    {
        return b < a;
    }

    typedef LifetimeTracker** TrackerArray;
    extern TrackerArray pTrackerArray; // extern -> 다른 파일에서 선언된 전역변수를 사용가능
    extern unsigned int elements;

    // Helper for destroying objects
    template <typename T>
    struct Deleter
    {
        static void Delete(T* pObj)
        {
            delete pObj;
        }
    };

    template <typename T, typename Destroyer>
    class ConcreteLifetimeTracker : public LifetimeTracker
    {
        private:
            T* pTracked;
            Destroyer destroyer;
            void AtExitFn();
        public:
            ConcreteLifetimeTracker(T* p, unsigned int longevity, Destroyer d) 
                : LifetimeTracker(longevity), pTracked(p), destroyer(d) {}
            ~ConcreteLifetimeTracker()
            {
                destroyer(pTracked);
            }
    };

    template <typename T, typename Destroyer>
    void SetLongevity(T* pDynObject, unsigned int longevity, Destroyer d = Private::Deleter<T>::Delete)
    {
        TrackerArray pArray = static_cast<TrackerArray>(std::realloc(pTrackerArray, sizeof(*pTrackerArray)*(elements + 1)));
        
        if(!pArray) throw std::bad_alloc();

        pTrackerArray = pArray;
        LifetimeTracker* p = new ConcreteLifetimeTracker<T, Destroyer>(pDynObject, longevity, d);
        TrackerArray pos = std::upper_bound(pTrackerArray, pTrackerArray+elements, longevity);
        std::copy_backward(pos, pTrackerArray+elements, pTrackerArray+elements+1);
        *pos = p;
        ++elements;
        std::atexit(AtExitFn);
    }

    static void AtExitFn()
    {
        assert(elements > 0 && pTrackerArray != 0);
        LifetimeTracker* pTop = pTrackerArray[elements-1];
        pTrackerArray = static_cast<TrackerArray>(std::realloc(pTrackerArray, sizeof(*pTrackerArray)*--elements));
        delete pTop;
    }
};

class A {};

class Derived : public A {};

template<class T, template<class> class CreatePolicy, template<class> class LifetimePolicy, template<class> class ThreadingModel>
class SingletonHolder
{
    public:
        static T& getInstance();

    private:
        SingletonHolder();
        static void DestroySingleton();

        typedef ThreadingModel<T>::VolatileType InstanceType;
        static InstanceType* pInstance;
        static bool destroyed;
};

int main()
{
    Singleton& singleton = singleton.getInstance();

    int* temp = new int[7];
    for(int i=0; i<7; ++i)
    {
        temp[i] = i;
    }

    int num = 7;
    int* newTemp = static_cast<int*>(std::realloc(temp, sizeof(*temp)*(num+1)));
    delete [] temp;
    temp = newTemp;
    int add = 4;
    int* pos = std::upper_bound(temp, temp+num, add);
    std::copy_backward(pos, newTemp+num, newTemp+num+1);
    std::cout << *pos << " " << *(newTemp+num) << std::endl;
    *pos = add;
    ++num;

    for(int i=0; i<num; ++i)
    {
        std::cout << newTemp[i] << " ";
    }
    std::cout << std::endl;

    add =50;
    std::vector<int> v = {12071, 77, 77, 40, 16, 2}; // { 2, 16, 40, 77, 77, 12071 };
    v.resize(7);

    for(int i=0; i<v.size();++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int>::iterator first, last, insert;
    insert = std::upper_bound(v.begin(), v.end(), add, Private::Check);
    first = v.begin();
    std::cout << "First : " << *insert << " " << *first << " " << *(first+5) << std::endl;
    std::copy_backward(insert, first+6, first+7);
    *insert = add;
    for(int i=0; i<v.size();++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    
}

