// string_impl.c - Implements some functions in string.h
// http://www.cplusplus.com/reference/cstring/

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// copying
// copying block of memory
// copys the values of num bytes from src directory to the memory block pointed to by dst.
void* m_memcpy(void* dst, const void* src, size_t num) {
}

// move block of memory
void* m_memmove(void* dst, const void* src, size_t num) {

}

// copy string
char* m_strcpy(char* dst, const char* src) {
    assert(dst != NULL);
    assert(src != NULL);
    // 包含结束符
    char* ptr = dst;
    while(*src)
        *ptr++ = *src++;
    *ptr = '\0';
    return dst;
}

char* m_strncpy(char* dst, const char* src, size_t num) {
    // 溢出：size_t递减到0后又回到最大的unsigned
    assert(dst != NULL);
    assert(src != NULL);
    // 若strlen(src)不足num，则追加结束符
    // 否则，不必显式追加结束符
    // 遍历num，有则拷贝，无则使用结束符替代
    char* ptr = dst;
    while(num > 0) {
        if(*src) *ptr++ = *src++;
        else *ptr++ = '\0';
        num -= 1;
    }
    return dst;
}

// concatenation
char* m_strcat(char* dst, const char* src) {
    assert(dst != NULL);
    assert(src != NULL);
    // 追加src到dst的末尾
    // 包含结束符
    char* ptr = dst;
    while(*dst++)
        ptr++;
    while(*src)
        *ptr++ = *src++;
    *ptr = '\0';
    return dst;
}

char* m_strncat(char* dst, const char* src, size_t num) {
    assert(dst != NULL);
    assert(src != NULL);
    // 从src拷贝至多num个字符到dst末尾
    // 追加结束符
    char *ptr = dst;
    while(*dst++)
        ptr++;
    while(num > 0) {
        if(*src) *ptr++ = *src++;
        else break;
        num -= 1;
    }
    *ptr = '\0';
    return dst;
}

// comparison
int m_memcmp(const char* ptr1, const char* ptr2, size_t num) {

}

int m_strcmp(const char* str1, const char* str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);
    // 比较
    while(*str1 && *str2) {
        if(*str1 > *str2) return 1;
        if(*str1 < *str2) return -1;
        str1++; str2++;
    }
    if(*str1) return 1;
    if(*str2) return -1;
    return 0;
}

int m_strncmp(const char* str1, const char* str2, size_t num) {
    assert(str1 != NULL);
    assert(str2 != NULL);
    // 如果strlen(str1) >= num && strlen(num2) >= num，则一直比较num个字符
    // 否则，则至少有一个字符串长度不足num，此时如果两个str都不足，则返回0，否则返回1或-1
    while(num != 0) {
        if(!(*str1) || !(*str2)) {
            if(*str1) return 1; // *str1与'\0'的比较，自然为>0
            if(*str2) return -1;// '\0'与*str2的比较，自然为<0
            return 0;   // '\0'与'\0'的比较，自然为0
        }
        if(*str1 > *str2) return 1;
        if(*str1 < *str2) return -1;
        str1++; str2++;
        num--;
    }
    return 0;
}

// searching
const void* m_memchr(const void* ptr, int value, size_t num) {

}

const char* m_strchr(const char* str, int character) {
    assert(str != NULL);
    // 找出第一次出现字符的位置，否则返回NULL
    while(*str) {
        if(*str == character)
            return str;
        str++;
    }
    return NULL;
}

const char* m_strrchr(const char* str, int character) {
    assert(str != NULL);
    // 找出最后一次出现字符的位置，否则返回NULL
    const char* ptr = NULL;
    while(*str) {
        if(*str == character)
            ptr = str;
        str++;
    }
    return ptr;
}

const char* m_strpbrk(const char* str1, const char* str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);
    // 查找str2中任意字符在str1第一次出现的位置，否则返回NULL
    const char* ptr;
    while(*str1) {
        ptr = str2;
        while(*ptr) {
            if(*str1 == *ptr) return str1;
            ptr++;
        }
        str1++;
    }
    return NULL;
}

const char* m_strstr(const char* str1, const char* str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);
    // 查找str1中第一次出现str2的位置or NUll
    // TODO KMP算法
    while(*str1) {
        if(m_strncmp(str1, str2, strlen(str2)) == 0) return str1;
        str1++;
    }
    return NULL;
}

char* m_strtok(char* str, const char* delimiters) {
    // split string into tokens
    static const char* start = NULL;
    if(start == NULL) {
        assert(str != NULL);
        start = str;
    }
    assert(start != NULL);
    assert(delimiters != NULL);

    const char* pos;
    while(*start) {
        pos = m_strpbrk(start, delimiters);
        if(pos > start) {
            char* buf = (char*)malloc(sizeof(char) * (pos-start+1));
            m_strncpy(buf, start, pos-start);
            buf[pos-start+1] = '\0';
            start = pos+1;
            return buf;
        }
        start = pos + 1;
    }
    start = NULL;
    return NULL;
}

size_t m_strlen(const char* str) {
    assert(str != NULL);
    size_t num = 0;
    while(*str++)
        num++;
    return num;
}

void* m_memset(void* ptr, int value, size_t num) {

}

int main(int argc, char const *argv[]) {

    char buf1[100], buf2[100];

    assert(m_strlen("abc") == strlen("abc"));

    m_strcpy(buf1, "abcd");
    strcpy(buf2, "abcd");
    assert(strcmp(buf1, buf2) == 0);

    m_strncpy(buf1, "abcd", 3);
    buf1[3] = '\0';
    strncpy(buf2, "abcd", 3);
    buf2[3] = '\0';
    assert(strcmp(buf1, buf2) == 0);

    m_strncpy(buf1, "abcd", 10);
    strncpy(buf2, "abcd", 10);
    assert(strcmp(buf1, buf2) == 0);

    m_strcat(buf1, "efg");
    strcat(buf2, "efg");
    assert(strcmp(buf1, buf2) == 0);

    m_strncat(buf1, "hijk", 2);
    strncat(buf2, "himn", 2);
    assert(strcmp(buf1, buf2) == 0);

    assert(m_strncmp("abc", "abxx", 2) == strncmp("abc", "abxx", 2));
    assert(m_strncmp("abc", "abxx", 3) == strncmp("abc", "abxx", 3));
    assert(m_strncmp("ab", "abxx", 3) == strncmp("ab", "abxx", 3));
    assert(m_strncmp("ab", "a", 3) == strncmp("ab", "a", 3));

    char buf3[] = "abcabc";
    assert(m_strchr(buf3, 'a') == strchr(buf3, 'a'));
    assert(m_strchr(buf3, 'd') == strchr(buf3, 'd'));
    assert(m_strrchr(buf3, 'a') == strrchr(buf3, 'a'));
    assert(m_strrchr(buf3, 'd') == strrchr(buf3, 'd'));

    char buf4[] = "This is a simple example";
    assert(m_strpbrk(buf4, "aeiou") == strpbrk(buf4, "aeiou"));
    assert(m_strpbrk(buf4, "xyz") == strpbrk(buf4, "xyz"));

    assert(m_strstr(buf4, "is") == strstr(buf4, "is"));


    char buf5[] = "- This, a sample string.";
    char delimiters[] = " ,.-";
    char* pch1;
    pch1 = m_strtok(buf5, delimiters);
    while(pch1 != NULL) {
        printf("%s\n", pch1);
        // free(pch1);
        pch1 = m_strtok(NULL, delimiters);
    }

    return 0;
}