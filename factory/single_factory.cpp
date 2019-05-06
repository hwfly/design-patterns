/**
 * 简单工厂模式
 * 
 * 主要特点是需要在工厂类中做判断，从而创造相应的产品，当增加新产品时，需要修改工厂类
*/

#include <iostream>

using namespace std;

typedef enum {
    T80 = 1,
    T99
} TankType;

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
    Tank* createTank(TankType type) {
        switch (type) {
        case 1:
            return new Tank80();

        case 2:
            return new Tank99();

        default:
            return NULL;
        }
    }
};

int main() {
    TankFactory* pfactory = new TankFactory();

    Tank* ptank = pfactory->createTank(T80);
    ptank->message();
    delete ptank;

    ptank = pfactory->createTank(T99);
    ptank->message();
    delete ptank;

    delete pfactory;

    return 0;
}