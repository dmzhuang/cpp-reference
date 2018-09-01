#include <iostream>
#include <iterator>

class MyIterator : public std::iterator<std::input_iterator_tag, int> {
    int* p;
public:
    MyIterator(int* x) : p(x) {}
    MyIterator(const MyIterator& mit) : p(mit.p) {}
    MyIterator& operator++() {++p; return *this;}
    MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
    bool operator==(const MyIterator& rhs) const {return p == rhs.p;}
    bool operator!=(const MyIterator& rhs) const {return p != rhs.p;}
    int& operator*() {return *p;}
};

int main(int argc, char const *argv[])
{
    int numbers[] = {10,20,30,40};
    MyIterator from(numbers);
    MyIterator until(numbers+3);
    for(auto iter = from; iter != until; ++iter)
        std::cout << *iter << " ";
    std::cout << "\n";
    return 0;
}