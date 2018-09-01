// Standard Tempate Library: Algorithms
// The header <algorithm> defines a collection of functions especially designed
// to be used on ranges of elements.
#include <algorithm>
#include <array>
#include <iostream>

template <class InputIterator1, class InputIterator2>
bool my_equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    while(first1 != last1) {
        if(*first1 != *first2)
            return false;
        ++first1; ++first2;
    }
    return true;
}

int main(int argc, char const *argv[])
{

    // non-modifying sequence operations
    std::array<int,8> foo = {1,2,3,4,5,6};
    if(std::all_of(std::begin(foo), std::end(foo),
        [](int& i) {return i%2;}))
        std::cout << "all are odd" << std::endl;
    if(std::any_of(std::begin(foo), std::end(foo),
        [](int& i) {return i%2;}))
        std::cout << "any are odd" << std::endl;
    if(std::none_of(std::begin(foo), std::end(foo),
        [](int& i) {return i%2;}))
        std::cout << "none are odd" << std::endl;

    std::for_each(std::begin(foo), std::end(foo),
        [](int& i) {std::cout << i << std::endl;});

    // find find_if find_if_not find_end find_first_of adjacent_find
    auto iter = std::find(std::begin(foo), std::end(foo), 3);
    iter = std::find_if(std::begin(foo), std::end(foo),
        [](int& i) {return i>3;});
    if(iter != std::end(foo))
        std::cout << "find " << *iter << std::endl;

    // count count_if
    // mismatch
    // equal
    // is_permutation
    // search


    // modifying sequence operations
    std::vector<int> vec(8);
    std::copy(std::begin(foo), std::end(foo), std::begin(vec));
    for_each(std::begin(vec), std::end(vec),
        [](int& i) {std::cout << i << std::endl;});
    // OutputIterator copy_n(InputIterator first, Size n, OutputIterator result);
    // OutputIterator copy_if(InputIterator first1, InputIterator last1, OutputItertor result, UnaryPredicate pred);
    // OutputIterator copy_backward(InputIterator first, InputIterator last, OutputIterator result) {
    //     while(last != first)
    //         *(--result) = *(--last);
    //     return result;
    // }

    // move move_backward
    // swap swap_ranges
    std::transform(std::begin(foo), std::end(foo), std::begin(foo),
        [](int i) {return i*2;});

    // generate



    // partitions

    // sorting

    // binary search

    // merge

    // heap

    // min/max

    // other

    return 0;
}