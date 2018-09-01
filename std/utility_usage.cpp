#include <utility>  // std::pair std::make_pair
#include <iostream>

// template <class T1, class T2>
// std::pair<V1,V2> make_pair(T1&& x, T2&& y);

int main(int argc, char const *argv[])
{
    std::pair<int,int> foo, bar;

    foo = std::make_pair(10,20);
    bar = std::make_pair(10.5,'a');

    std::cout << "foo:" << foo.first << " " << foo.second << std::endl;
    std::cout << "bar:" << bar.first << " " << bar.second << std::endl;
    return 0;
}