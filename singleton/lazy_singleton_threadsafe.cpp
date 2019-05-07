/**
 * 单例模式
 *
 * 保证一个类仅有一个实例，并提供一个访问它的全局访问点。
 *
 * 主要解决：一个全局使用的类频繁地创建与销毁。
 * 何时使用：想控制实例数目，节省系统资源的时候。
 * 如何解决：判断系统是否已存在单例，如果有则返回，没有则创建。
 * 关键代码：构造函数是私有的。
 *
 * 单例大约有两种实现方法：懒汉与饿汉。
 *
 * 懒汉：故名思义，不到万不得已就不会去实例化类，也就是说在第一次用到类实例的时候才会去实例化，所以上边的经典方法被归为懒汉实现；
 * 饿汉：饿了肯定要饥不择食。所以在单例类定义的时候就进行实例化。
 *
 * 特点与选择：
 * 由于要进行线程同步，所以在访问量比较大，或者可能访问的线程比较多时，采用饿汉实现，可以实现更好的性能。这是以空间换时间。
 * 在访问量较小时，采用懒汉实现。这是以时间换空间。
*/

#include <iostream>
#include <mutex>

//懒汉式一般实现：加lock，线程安全，getInstance返回的实例指针需要delete

class Singleton {
public:
    static Singleton* getInstance();
    ~Singleton() {}

private:
    static Singleton* m_pSingleton;
    static std::mutex m_mutex;
    Singleton() {}
    Singleton(const Singleton& obj) = delete;  //明确拒绝
    Singleton& operator=(const Singleton& obj) = delete; //明确拒绝
};

Singleton* Singleton::m_pSingleton = NULL;
std::mutex Singleton::m_mutex;

Singleton* Singleton::getInstance() {
    if (m_pSingleton == NULL) {
        m_mutex.lock();
        m_pSingleton = new Singleton;
        m_mutex.unlock();
    }

    return m_pSingleton;
}
//END

int main() {
    Singleton* instance = Singleton::getInstance();
    delete instance;

    return 0;
}