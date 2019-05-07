/**
 * 在C++11标准中，要求局部静态变量初始化具有线程安全性，因此以下单例实现是线程安全的
 * 
 * 更多解释：https://blog.csdn.net/imred/article/details/89069750
 * 实现示例：https://blog.csdn.net/u011726005/article/details/82356538
*/
#include <iostream>

class Singleton
{
public:
    static Singleton& instance() {
        static Singleton instance;
        return instance;
    }

    // disable copying
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&) = delete;

private:
    Singleton() {};
    ~Singleton() {};
};

int main() {
    Singleton & instance = Singleton::instance();
    return 0;
}
