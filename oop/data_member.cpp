#include <iostream>
#include <cassert>
using namespace std;

// 预处理器指令
#define str(x) #x // 将参数x的值转换为字符串常量
#define concat(a, b) a ## b // 将两个参数连接到一起

#ifndef __cplusplus
#error A C++ compiler is required!
#endif

#define print_sizeof(base) cout << "sizeof(" << #base << "): " << sizeof(base) << endl


// 典型的菱形继承
class X {};
class YY : public X {};
class Y : public virtual X {};
class Z : public virtual X {};
class A : public Y, public Z {};


class Point3d {
private:
    float x;
private:
    float y;
private:
    float z;
};

template <class class_type,
          class data_type1,
          class data_type2>
char* access_order(data_type1 class_type::*mem1, data_type2 class_type::*mem2) {
    assert(mem1 != mem2);
    return mem1 < mem2 ? "member 1 occurs first" : "member 2 occurs first";
}
// access_order(&Point3d::z, &Point3d::y);


class DupDataMemBase {
public:
    DupDataMemBase(int f) : foo(f) {}
    void fun() {cout << "(Base) foo = " << foo << endl;}
protected:
    int foo;
};

class DupDataMemDev : public DupDataMemBase {
public:
    DupDataMemDev(int f) : DupDataMemBase(0), foo(f) {}
    void fun() {
        cout << "(Derived) Base::foo = " << DupDataMemBase::foo << endl;
        cout << "(Derived) foo = " << foo << endl;
    }
private:
    int foo;
};

class Point {
public:
    Point(int _x) : x(_x) {}
    virtual ~Point() {}
    virtual void vfunc1() const {}
    virtual void vfunc2() {}
    void bar() {}
    static void fun() {}
    int x;
};

class Point2d : public Point {
public:
    Point2d(int _x, int _y) : Point(_x), y(_y) {}
    ~Point2d() override {}
    virtual void vfunc1() const override {}
    void bar() {}
    int y;
};


int main(int argc, char const *argv[]) {

    Point p1(100);
    Point2d p2(100, 101);

    // concat(c, out) << str(test) << endl;

    // X/Y/Z/A中没有任何一个包含明显的数据,其间只表示了继承关系。
    print_sizeof(X);    // 1，空类有一个隐晦的char，用来避免两个object具有相同的地址
    print_sizeof(Y);    // 8
    print_sizeof(YY);   // 1
    print_sizeof(Z);    // 8
    print_sizeof(A);    // 16

    // X：一个空的class的size并不是空的，它有一个隐晦的1byte。那是被编译器安插进去的一个char。
    // 这使得两个X的object得以在内存中配置独一无二的地址。
    X a, b;
    if(&a == &b) cerr << "yipes!" << endl;

    // Y和Z的大小受到3个因素的影响：
    // 1、语言本身所造成的额外负担
    // virtual base class：派生类存在指针，指向virtual base class subobject或者一个相关表格
    // 表格中存放的若不是virtual base class subobject的地址就是其offset
    // 2、编译器对特殊情况所提供的优化处理
    // 传统上base class subobject被放在derived class的固定部分的尾端，某些编译器会对empty virtual base class提供特殊支持
    // 3、Alignment的限制
    // 对齐就是将数值调整到某数的整数倍，以使bus的运输量达到最高效率

    cout << "--------\n";
    print_sizeof(DupDataMemBase);
    print_sizeof(DupDataMemDev);
    DupDataMemBase ddmb(1);
    DupDataMemDev ddmd(1);
    ddmb.fun();
    ddmd.fun();


    return 0;
}