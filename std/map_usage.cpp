#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;
using Pet_type = string;
using Pet_name = string;

int main(int argc, char const *argv[])
{
    std::multimap<Pet_type, Pet_name> pets;
    pets.insert({
        {"pig", "Peter"},
        {"rabbit", "Becky"},
        {"pig", "Tom"},
        {"Dog", "Vivian"}
    });

    auto iter = pets.lower_bound("Dog");
    if(iter != pets.end()) {
        // 这里使用emplace_hint，将得到LIFO的效果
        pets.emplace_hint(iter, "Dog", "York");
    } else {
        pets.emplace("Dog", "Ken");
    }


    for(auto iter = pets.begin(); iter != pets.end(); ) {
        auto pr = pets.equal_range(iter->first);
        cout << iter->first << " => ";
        for(auto it = pr.first; it != pr.second; ++it)
            cout << it->second << " ";
        cout << endl;
        // 注意，这里将iter设为这个序列的结束迭代器，它也是指向下一个pet类型的迭代器或者是容器的结束迭代器
        iter = pr.second;
    }


    return 0;
}