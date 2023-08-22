#include <iostream>
#include <string>

using namespace std;

class IPerson
{
    public:
        IPerson()
        {}

        virtual string name() const = 0;
        virtual string birthDate() const = 0;
        
};

class PersonInfo
{
    public:
        virtual const char* theName() const;
        virtual const char* theBirthDate() const;

        virtual const char* valueDelimOpen() const
        {
            return "[";
        }
        virtual const char* valueDelimClose() const
        {
            return "]";
        }
};


// Use public inheritance to create a 'is a' relationship with IPerson interface(Abstract class)
// Use private inheritance for only implementation of PersonInfo, which creates a 'is implemented in terms of' relationship
// 
class CPerson : public IPerson, private PersonInfo
{
    public:
        CPerson(string name, string birthDate) : name(name)
        {}

        virtual string name() const
        {
            return PersonInfo::theName();
        }

        virtual string birthDate() const
        {
            return PersonInfo::theBirthDate();
        }
    
    private:
        virtual const char* valueDelimOpen() const
        {
            return "{";
        }

        virtual const char* valueDelimClose() const
        {
            return "}"
        }
};

int main()
{
    CPerson cp;
    cp.theName(); // Error, as CPerson inherit 'PersonInfo' as private, all the data member in PersonInfo will be private in CPerson
}

