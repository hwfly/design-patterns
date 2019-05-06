/**
 * 工厂方法模式
 *
 * 是指定义一个创建对象的接口，让子类决定实例化哪一个类，Factory Method使一个类的实例化延迟到其子类。
 *
 * 主要解决：主要解决接口选择的问题。
 * 何时使用：我们明确地计划不同条件下创建不同实例时。
 * 如何解决：让其子类实现工厂接口，返回的也是一个抽象的产品。
 * 关键代码：创建过程在其子类执行。
 * 缺点：每增加一种产品，就需要增加一个对象工厂。相比简单工厂模式，工厂方法模式需要定义更多的类。
*/

#include <iostream>

using namespace std;

class Tank {
public:
    virtual void message() = 0;
    virtual ~Tank() = default;
};

class Tank80: public Tank {
public:
    void message() {
        cout << "Tank80" << endl;
    }
};

class Tank99: public Tank {
public:
    void message() {
        cout << "Tank99" << endl;
    }
};

class TankFactory {
public:
    virtual Tank* createTank() = 0;
    virtual ~TankFactory() = default;
};

class Tank80Factory: public TankFactory {
public:
    Tank* createTank() {
        return new Tank80();
    }
};

class Tank99Factory: public TankFactory {
public:
    Tank* createTank() {
        return new Tank99();
    }
};

int main() {
    TankFactory* pfactory = new Tank80Factory();
    Tank* ptank = pfactory->createTank();
    ptank->message();
    delete ptank;
    delete pfactory;

    pfactory = new Tank99Factory();
    ptank = pfactory->createTank();
    ptank->message();
    delete ptank;
    delete pfactory;

    return 0;
}