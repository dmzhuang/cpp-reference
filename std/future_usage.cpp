#include <future> // std::future std::async
#include <chrono> // std::chrono::milliseconds
#include <iostream>
#include <thread>

// future对象
// future::get()阻塞直到ready
// future::valid()检查是否valid
// future::wait()等待直到ready
// future::wait_for()等待一定时间，wait_until()等待到某个时刻
    // 返回std::future_status::timeout | ready | deferred
// 产生future的3种方式
//  async
//  promise::get_future
//  packaged_task::get_future

// std::async(launch, fn, args)
// 异步地调用函数，返回一个std::future对象
    // launch: std::launch::aync | std::launch::deferred

// promise
    // future为消费者，promise为生产者
// promise::get_future()只能有一个future
// promise::set_value() / set_exception() / set_value_at_exit() / set_exception_at_exit()

// packaged_task
    // future为消费者，packaged_task为生产者
// packaged_task::get_future()只能有一个future


bool is_prime(int x) {
    for(int i = 2; i < x; ++i)
        if(x % i == 0) {
            std::cout << "done\n";
            return false;
        }
    std::cout << "done\n";
    return true;
}

void print_int(std::future<int>& fut) {
    std::cout << "thread waiting...\n" ;
    int x = fut.get();
    std::cout << "value = " << x << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "thread ends\n";
}

int main(int argc, char const *argv[])
{
    // // call function asynchronously
    // std::launch::deferred | std::launch::async
    std::future<bool> fut = std::async(std::launch::async, is_prime, 700020007);

    std::cout << "checking, please wait\n";
    std::chrono::milliseconds span(200);
    // fut.wait_until()
    // while(fut.wait_for(span) == std::future_status::timeout)
    //     std::cout << "." << std::flush;

    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "thread woke up\n";

    bool x = fut.get();

    // bool x = is_prime(700020007);
    std::cout << (x ? "is prime" : "is not prime") << "\n";

    std::cout << "-----\n";

    std::promise<int> pro;
    std::future<int> fut2 = pro.get_future();

    std::thread th(print_int, std::ref(fut2));
    pro.set_value(20);
    // pro.set_exception()

    th.join();

    std::cout << "-------\n";
    std::packaged_task<int(int)> tsk([](int x) -> int {
        return x * 3;
    });

    std::future<int> fut3 = tsk.get_future();
    tsk(100);
    int ans = fut3.get();
    std::cout << "ans = " << ans << "\n";

    tsk.reset();
    fut3 = tsk.get_future();
    std::thread(std::move(tsk), 33).detach();

    ans = fut3.get();
    std::cout << "ans = " << ans << "\n";


    return 0;
}