#include <iostream>
#include <chrono>
#include "SimpleClass.h"
#include <iomanip>
//#include "Log_Ptr.h"
using namespace std;




std::string GetTimestamp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm timeinfo;
    localtime_s(&timeinfo, &now_c);
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%c", &timeinfo);

    return std::string(buffer);
}

class Counter
{
public:
    Counter() : _counter(0) {};
    Counter(const Counter&) = delete;
    Counter& operator = (const Counter&) = delete;

    ~Counter() {}

    void reset() { _counter = 0; }
    unsigned int Get() { return _counter; }

    //operators
    void operator++() { _counter++; }
    void operator++(int) { _counter++; } //or add int??
    void operator--() { _counter--; }
    void operator--(int) { _counter--; }

    ////overloading << operator... ? 
    //friend std::ostream& operator<<(std::ostream& os, const Counter& counter)
    //{
    //    os << "Counter Value: " << counter._counter << "\n";
    //    return os;
    //}

private:
    unsigned int _counter{};

};

template<class T>
class Log_Ptr
{
public:
    //constructor
    explicit Log_Ptr(T* ptr = nullptr)
    {
        
        _ptr = ptr;
        _counter = new Counter();
        (*_counter)++;
        


        // vois testata std_puttime timestampin sijaan
        std::cout << GetTimestamp() << " omistajuus siirretty " << _ptr << "\n";
        std::cout << "counter: "<<_counter->Get() << "\n";
    }

    //copy constructor
    Log_Ptr(Log_Ptr<T>& sp)
    {
        _ptr = sp._ptr;
        _counter = sp._counter;
        (*_counter)++;
        std::cout << "counter: " << _counter->Get() << "\n";
    }
    //references count
    unsigned int use_count() { return _counter->Get(); }

    //Get the pointer
    T* get() { return _ptr; }

    //Overload * operator ..
    T& operator*() {
        std::cout<<GetTimestamp() << " operator * " << _ptr << "\n";return *_ptr;
    }

    //Overload -> operator
    T* operator ->() {
        std::cout << GetTimestamp()<< " operator ->" << _ptr << "\n"; return _ptr;
    }

    

    Log_Ptr(const Log_Ptr&) = delete; //delete copy constructor?

    Log_Ptr& operator = (const Log_Ptr&) = delete; //delete copy assignment operator

    //DESTRO
    ~Log_Ptr() {
        (*_counter)--;
        if (_counter->Get() == 0)
        {
            std::cout << GetTimestamp()<<" olio tuhottu " << _ptr << "\n";

            delete _counter;
            delete _ptr;
            
        }
        else
        {
            std::cout <<GetTimestamp() << " yksi pointteri poistettu, jäljellä: " << _ptr<<" " << _counter->Get() << "\n";
        }
    }

    ////friend?
    //friend ostream& operator <<(ostream& os, Log_Ptr<T>& sp)
    //{
    //    os << "Address pointed: " << sp.get() << "\n";
    //    os << *(sp_counter) << "\n";
    //    return os;
    //}


private:
    T* _ptr;
    Counter* _counter;
};

//Test creating inside a method..
template<class T>
void CreateAndUse(T t)
{
    t->Act();
}


int main() {

    SimpleClass* sc = new SimpleClass(45);
    Log_Ptr<SimpleClass> sp1(sc);
    sp1->Act();
    (*sp1).Act();

    CreateAndUse(sp1);

    Log_Ptr<SimpleClass> sp2 = sp1;
   sp2->Act();

    Log_Ptr<SimpleClass> sp3 = sp1;



    return 0;
}

