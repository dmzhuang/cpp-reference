#include <mutex> // std::mutex
#include <chrono> // std::chrono::milliseconds
#include <thread> // std::thread
#include <iostream> // std::cout
#include <vector>   // std::vector
#include <stdexcept> // std::logic_error

// mutex 互斥量
// recursive_mutex 递归互斥量，允许同一个线程对它已经获得的lock再次lock，释放时也要unlock相同的次数
// timed_mutex 定时互斥量，主要是在try_lock时可以定时try_lock_for和try_lock_until
// recursive_timed_mutex 递归定时互斥量

// lock_guard
// 使一个mutex对象保持locked状态
// lock_guard(mtx)：lock这个mtx
// ~lock_guard(): unlock这个mtx
// 保证了在抛出异常的情况下mtx依然能被正确unlock

// unique_lock

// call_once


std::mutex mtx_for_lockguard;
void print_even(int x) {
    if(x%2 == 0) std::cout << x << "\n";
    else throw (std::logic_error("not even"));
}

void thread_func(int x) {
    try {
        std::lock_guard<std::mutex> lck(mtx_for_lockguard);
        print_even(x);
    } catch(std::logic_error&) {
        std::cout << "[exception caught]\n";
    }
}

int counter = 0;

int main(int argc, char const *argv[])
{
    std::vector<std::thread> threads;

    // 普通mutex
    std::mutex mtx;
    for(int i = 0; i < 10; ++i) {
        threads.push_back(std::thread([&mtx](int n) {
            mtx.lock();
            std::cout << "thread #" << std::this_thread::get_id() << "\n";
            for(int i = 0; i < 10; ++i)
                ++counter;
            mtx.unlock();
        }, i));
    }

    // 定时mutex
    std::timed_mutex timed_mtx;
    for(int i = 0; i < 10; ++i) {
        threads.push_back(std::thread([&timed_mtx](int n) {
            while(!timed_mtx.try_lock_for(std::chrono::milliseconds(200))) {
                std::cout << "-"; //-- thread #" << std::this_thread::get_id() << "\n";
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "*\n";
            // std::cout << "thread #" << std::this_thread::get_id() << " ends\n";
            timed_mtx.unlock();
        }, i));
    }

    for(int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(thread_func, i+1));
    }



    for(auto& th : threads)
        th.join();

    std::cout << "counter = " << counter << "\n";

    return 0;
}