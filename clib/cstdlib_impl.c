// stdlib_impl.c - Implements some functions in stdlib.h
// http://www.cplusplus.com/reference/cstdlib/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// convert string to number
double m_atof(const char* str) {
}

int m_atoi(const char* str) {
    // str不为NULL，且以\0结尾
    // NUll断言
    // 负数处理
    // 非数字处理
    assert(str != NULL);
    int result = 0, flag = 1;
    const char* ptr = str;
    if(*str == '-') {
        flag = -1;
        ptr++;
    }
    while(*ptr) {
        if(*ptr < '0' || *ptr > '9')
            break;
        result = result * 10 + (*ptr - '0');
        ptr++;
    }
    result *= flag;
    return result;
}

// long m_atol(const char* str) {

// }

// long long m_atoll(const char* str) {

// }

// double m_strtod(const char* str) {

// }

// float m_strtof(const char* str) {

// }

long m_strtol(const char* str) {

}

long double m_strtold(const char* str) {

}

long long m_strtoll(const char* str) {

}

unsigned long m_strtoul(const char* str) {

}

unsigned long long m_strtoull(const char* str) {

}

// dynamic memory management
// calloc
// free
// malloc
// realloc

// searching and sorting
void* m_bsearch(const void* key,
                const void* base,
                size_t num,
                size_t size,
                int (*compar)(const void*, const void*)) {
}

void m_qsort(void* base, size_t num, size_t size,
             int (*compar)(const void*, const void*)) {

}

int main(int argc, char const *argv[]) {

    assert(m_atoi("123") == atoi("123"));
    assert(m_atoi("-123") == atoi("-123"));
    assert(m_atoi("-g23") == atoi("-g23"));


    return 0;
}