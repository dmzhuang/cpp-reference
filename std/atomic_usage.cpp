// construct atomics
#include <iostream> // std::cout
#include <atomic> // std::atomic
#include <thread> // std::thread
#include <vector> // std::vector
#include <sstream> // std::stringstream

std::atomic<bool> ready(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT; // boolean: test_and_set() and clear()
// atomic_flag can be used a a lock

void count1m(int id) {
    bool x;
    do {
        x = ready.load(std::memory_order_relaxed);
        if(x) break;
        std::this_thread::yield();
    } while(!x);
    // while(!ready) {std::this_thread::yield();}  // wait for the ready signal
    for(volatile int i = 0; i < 10000000; ++i) {}
    if(!winner.test_and_set()) {std::cout << "thread #" << id << " won\n";}
    // return true if the flag was set before the call
}

std::atomic_flag lock = ATOMIC_FLAG_INIT;
std::stringstream stream;
void append_number(int n) {
    while(lock.test_and_set()) {std::this_thread::yield();}
    stream << "thread #" << n << "\n";
    lock.clear();
}

int main(int argc, char const *argv[])
{
    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count 1 million...\n";
    for(int i = 1; i <= 10; ++i)
        threads.push_back(std::thread(count1m, i));
    // ready = true;
    int i = 0;
    while(++i < 1000000000) {}
    ready.store(true, std::memory_order_relaxed);
    for(auto& th : threads) th.join();
    std::cout << "---" << std::endl;

    std::vector<std::thread> ths;
    for(int i = 1; i <= 10; ++i)
        ths.push_back(std::thread(append_number, i));
    for(auto& t : ths) t.join();

    std::cout << stream.str();

    return 0;
}