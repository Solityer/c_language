#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Date
{
public:
    Date(int year, int month, int day)
        : _year(year)
        , _month(month)
        , _day(day)
    {}
private:
    int _year;
    int _month;
    int _day;
};

class S
{
public:
    S(int a)
        :_a1(a)
    {}

    void Print() 
    {
        cout << _a1 << endl;
    }

private:
    int _a1;
};

class A
{
public:
    A() 
    { 
        ++_scount; 
    }
    A(const A & t) 
    { 
        ++_scount;
    }
    ~A()
    { 
        --_scount;
    }
    static int GetACount() 
    { 
        return _scount; 
    }
    class B  //内部类，天生就是外部类的友元，可以访问私有函数，外部类无法访问内部类
    {};
private:
    //不属于某个对象，属于所有对象，属于整个类
    static int _scount;
};

int A::_scount = 0; //定义初始化

void TestA()
{
    cout << A::GetACount() << endl;
    A a1, a2;
    A a3(a1);
    cout << A::GetACount() << endl;
}

int main()
{
    Date d(2024,3,12);
    
    S aa1(1);  //直接调用构造函数
    S aa2 = 1;   //隐式类型转换
    

    return 0;
}