// function objects
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

double my_divide(double x, double y) {return x/y;}
struct MyPair {
    double a, b;
    // non-static member function: has an implicit argument this
    double multiply(char c) {return a*b;}
};

struct int_holder {
    int value;
    int triple(int c) {return value * 3;}
};

struct IsOdd {
    bool operator()(int i) const {return i%2;}
    typedef int argument_type;
};

struct my_greater {
    // bool operator()(const int lhs, const int rhs) {return lhs > rhs;}
    bool operator()(int& lhs, int& rhs) {return lhs > rhs;}
    typedef int argument_type;
};

int half(int x) {return x/2;}
struct third_t {
    int operator()(int x) {return x/3;}
};
struct MyValue{
    int value;
    int fifth() {return value/5;}
};

int main(int argc, char const *argv[])
{
    // functions: create objects of wrapper classes based on its arguments

    // template <class Fn, class... Args>
    // bind(Fn&& fn, Args&&... args);
    // returns a function object based on fn, but with its argument bound to args.
    auto fn_five = std::bind(my_divide, 10, 2);
    std::cout << fn_five() << std::endl;
    auto fn_half = std::bind(my_divide, std::placeholders::_1, 2);
    std::cout << fn_half(21) << std::endl;
    auto fn_invert = std::bind(my_divide, std::placeholders::_2, std::placeholders::_1);
    std::cout << fn_invert(20, 10) << std::endl;

    MyPair ten_two{10,2};
    // &MyPair::multiply指向function member的指针
    // 因为是nonstatic，其第一个参数应该是this指针，所以需要把对象传递进去
    auto bound_member_fn = std::bind(&MyPair::multiply, std::placeholders::_1, 'A');
    std::cout << bound_member_fn(ten_two) << std::endl;
    auto bound_member_obj = std::bind(&MyPair::multiply, ten_two, std::placeholders::_1);
    std::cout << bound_member_obj('A') << std::endl;
    auto bound_member_data = std::bind(&MyPair::a, ten_two); // returns ten_two.a
    std::cout << bound_member_data() << std::endl;

    // construct reference_wrapper
    // construct an object to hold a reference to elem.
    // if the argument is itself a reference_wrapper, it creates a copy instead
    int val {10};
    int &rval = val;
    auto val_ref = std::ref(val);
    auto rval_ref = std::ref(rval); // std::ref to a reference is ok
    // auto rref = std::ref(1+2); // error, use of deleted function void std::ref(const T&&) = delete;
    ++val_ref;
    std::cout << "val = " << val << std::endl;
    std::cout << "rval = " << rval << std::endl;
    // cref

    // mem_fn
    // convert member function to function object
    // returns a function object whose functional call invokes the member function pointed by pm
    // template <class Ret, class T>
    // mem_fn(Ret T::*pm); // pm: Pointer to a member function
    int_holder five{5};
    std::cout << five.triple('a') << std::endl;        // call member directly
    auto triple = std::mem_fn(&int_holder::triple); // same as above using a mem_fn
    std::cout << "triple = " << triple(&five, 'a') << std::endl;
    // 第一个参数是T或Ｔ&或Ｔ*

    std::vector<int> v {11,3,4,2};
    // std::sort(v.begin(), v.end(), my_greater());
    // for_each(v.begin(), v.end(),
    //     [](int i) {std::cout << i << std::endl;});
    // std::sort(v.begin(), v.end(), std::not2(my_greater()));
    int count = std::count_if(v.begin(), v.end(), std::not1(IsOdd()));
    std::cout << "count = " << count << std::endl;

    // wrapper classes
    std::function<int(int)> fn1 = half;
    std::function<int(int)> fn2 = &half;
    std::function<int(int)> fn3 = third_t();
    std::function<int(int)> fn4 = [](int x) {return x/4;};

    // stuff with members
    std::function<int(MyValue)> value = &MyValue::value; // pointer to data member
    std::function<int(MyValue&)> fn = &MyValue::fifth; // pointer to function member
    MyValue sixty{60};
    std::cout << "value(sixty) " << value(sixty) << std::endl; // sixty.value
    std::cout << "fn(sixty) " << fn(sixty) << std::endl;    // sixty.fifth()

    // operator classes

    // other classes

    // namespace
    return 0;
}