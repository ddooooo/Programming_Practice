#include <iostream>
using namespace std;

class CompanyA
{
    public:
        void sendClearText(const string& msg);
        void sendEncrypted(const string& msg);
};

class CompanyB
{
    public:
        void sendClearText(const string& msg);
        void sendEncrypted(const string& msg);
};

class CompanyZ
{
    public:
        void sendEncrypted(const string& msg);
};

class MsgInfo {};


// Class for sending message to any tpye of Company
template <typename Company>
class MsgSender
{
    public:
        void sendClear(const MsgInfo& info)
        {
            string msg;
            Company c;
            c.sendClearText(msg);
        }

        void sendSecret(const MsgInfo& info)
        {
            string msg;
            Company c;
            c.sendEncryptedText(msg);
        }
};

// Class for logging the message sent to the company
// Compiler error: the problem is when compiler see class 'logMsgSender'
// it will never know the inheritance class of 'logMsgSender'
// The template paremeter 'Company' will remain unknown untill logMsgSender is created as instance
// Hence it is impossible to know what type MsgSender<Company> is
// And it wil never know whether MsgSender<Company> has a function 'sendClear(info)' or not 
template <typename Company>
class LogMsgSender : private MsgSender<Company> // private inheritance to inherit implementation class
{
    public:
        using MsgSender<Company>::sendClear; // Enlarge the scope of derived class

        void sendClearMsg(const MsgInfro& info) // As sendClear function in MsgSender is non-virtual function
        {
            // It is not possible to call sendClear, if Company == CompanyZ
            // This is why compiler refuse to search base class to find the Company
            sendClear(info);

            // There are three solutions to tell compiler to search all the base classes to call the function 'sendClear'
            // Solution #1
            this->sendClear(info);
            // Solution #2
            sendClear(info);
            // Solution #3 explicit -> it will ignore the virtual function binding -> not recommended
            MsgSender<Company>::sendClear(info);

        }
};

// Total template specialization
template<>
class MsgSender<CompanyZ>
{
    public:
        void sendSecret(const MsgInfo& info)
        {
            string msg;
            CompanyZ z;
            z.sendEncrypted(msg);
        }
};

int main()
{
    LogMsgSender<CompanyZ> zMsgSender;
    MsgInfo msgData;

    zMsgSender.sendClearMsg(msgData); // Compiler error: CompanyZ does not have a function sendClear
}