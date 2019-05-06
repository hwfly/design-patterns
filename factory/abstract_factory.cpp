/**
 * 抽象工厂模式
 *
 * 提供一个创建一系列相关或相互依赖的对象接口，而无需指定它们的具体类。
 *
 * 主要解决：主要解决接口选择的问题。
 * 何时使用：系统的产品有多于一个的产品族，而系统只消费其中某一族的产品。
 * 如何解决：在一个产品族里面，定义多个产品。
 * 关键代码：在一个工厂里聚合多个同类产品。
 * 缺点：产品族扩展非常困难，要增加一个系列的某一产品，既要在抽象的 Creator 里加代码，又要在具体的里面加代码。
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

class Plain {
public:
    virtual void message() = 0;
    virtual ~Plain() = default;
};

class Plain80: public Plain {
public:
    void message() {
        cout << "Plain80" << endl;
    }
};

class Plain99: public Plain {
public:
    void message() {
        cout << "Plain99" << endl;
    }
};

class Factory {
public:
    virtual Tank* createTank() = 0;
    virtual Plain* createPlain() = 0;
    virtual ~Factory() = default;
};

class Factory80: public Factory {
public:
    Tank* createTank() {
        return new Tank80();
    }
    Plain* createPlain() {
        return new Plain80();
    }
};

class Factory99: public Factory {
public:
    Tank* createTank() {
        return new Tank99();
    }
    Plain* createPlain() {
        return new Plain99();
    }
};

int main() {
    Factory* pfactory = new Factory80();

    Tank* ptank = pfactory->createTank();
    ptank->message();
    delete ptank;

    Plain* pplain = pfactory->createPlain();
    pplain->message();
    delete pplain;

    delete pfactory;


    pfactory = new Factory99();

    ptank = pfactory->createTank();
    ptank->message();
    delete ptank;

    pplain = pfactory->createPlain();
    pplain->message();
    delete pplain;

    delete pfactory;

    return 0;
}