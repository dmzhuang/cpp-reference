#include <thread> // std::thread
#include <atomic> // std::atomic
#include <functional> // std::ref
#include <chrono> // std::chrono::seconds
#include <vector>
#include <iostream>


/*
可用于初始化std::thread的“函数”类型有：
1、函数指针
    void func(int arg);
    std::thread(func, arg);
2、类成员函数指针
    class C {
    public:
        void func(int arg);
    };
    C c;
    std::thread(&C::func, &c, arg);
3、函数对象（重载调用运算符）
    class func {
    public:
        void operator()(int arg);
    };
    std::thread(C(), arg);
4、lambda表达式
    std::thread([](int arg) {}, arg);
5、function对象
    std::function<void(int)> f(func);
    std::thread(f, arg);
*/

std::atomic<int> global {0};

void increment_global(int n) {
    for(int i = 0; i < n; ++i)
        ++global;
}

void increment_reference(std::atomic<int>& obj, int n) {
    for(int i = 0; i < n; ++i)
        ++obj;
}

struct C {
    std::atomic<int> member;
    C() : member(0) {}
    void increment_member(int n) {
        for(int i = 0; i < n; ++i)
            ++member;
    }
};

std::atomic<bool> isdone {false};
void this_thread_test() {
    std::cout << std::this_thread::get_id() << " starts\n";
    // yield to other threads
    while(!isdone) {std::this_thread::yield();}
    std::cout << std::this_thread::get_id() << " ends\n";
}

struct increment_func {
    void operator()(std::atomic<int>& a, int n) {
        for(int i = 0; i < n; ++i)
            ++a;
    }
};

int main(int argc, char const *argv[])
{
    std::vector<std::thread> threads;

    // 使用函数指针创建thread
    for(int i = 1; i < 5; ++i)
        threads.push_back(std::thread(increment_global, 10));

    std::atomic<int> local {0};
    for(int i = 1; i < 5; ++i)
        threads.push_back(std::thread(increment_reference, std::ref(local), 10));

    // 使用类成员函数指针创建thread
    C obj;
    for(int i = 1; i < 5; ++i)
        threads.push_back(std::thread(&C::increment_member, &obj, 10));

    // 使用函数对象创建thread
    std::atomic<int> local_for_func {0};
    for(int i = 1; i < 5; ++i)
        threads.push_back(std::thread(increment_func(), std::ref(local_for_func), 10));

    // 使用function对象创建thread
    std::atomic<int> local_fun {0};
    std::function<void(std::atomic<int>&, int)> fobj(increment_reference);
    for(int i = 1; i < 5; ++i)
        threads.push_back(std::thread(fobj, std::ref(local_fun), 10));

    // 使用lambda表达式创建thread
    std::atomic<int> local_for_lambda {0};
    for(int i = 1; i < 5; ++i)
        threads.push_back(std::thread([&local_for_lambda](int n) {
            for(int i = 0; i < n; ++i)
                ++local_for_lambda;
        }, 10));

    std::atomic<int> local_for_lambda2 {0};
    for(int i = 1; i < 5; ++i)
        threads.push_back(std::thread([](std::atomic<int>& a, int n){
            for(int i = 0; i < n; ++i)
                ++a;
        }, std::ref(local_for_lambda2), 10));

    // 等待所有线程结束
    for(auto& th : threads)
        th.join();

    std::cout << "global = " << global << "\n";
    std::cout << "local = " << local << "\n";
    std::cout << "member = " << obj.member << "\n";
    std::cout << "local_for_func = " << local_for_func << "\n";
    std::cout << "local_fun = " << local_fun << "\n";
    std::cout << "local_for_lambda = " << local_for_lambda << "\n";
    std::cout << "local_for_lambda2 = " << local_for_lambda2 << "\n";

    std::cout << "----\n" << std::flush;

    std::thread last(this_thread_test);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    // std::this_thread::sleep_until();
    isdone = true;
    last.join();

    return 0;
}