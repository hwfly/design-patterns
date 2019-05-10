/**
 * 中介者模式（Mediator Pattern）
 *
 * 意图：用一个中介对象来封装一系列的对象交互，中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。
 * 主要解决：对象与对象之间存在大量的关联关系，这样势必会导致系统的结构变得很复杂，同时若一个对象发生改变，我们也需要跟踪与之相关联的对象，同时做出相应的处理。
 * 何时使用：多个类相互耦合，形成了网状结构。
 * 如何解决：将上述网状结构分离为星型结构。
 * 关键代码：对象 Colleague 之间的通信封装到一个类中单独处理。
 * 应用实例：
 *      1、中国加入 WTO 之前是各个国家相互贸易，结构复杂，现在是各个国家通过 WTO 来互相贸易。
 *      2、机场调度系统。
 *      3、MVC 框架，其中C（控制器）就是 M（模型）和 V（视图）的中介者。
 * 优点：
 *      1、降低了类的复杂度，将一对多转化成了一对一。
 *      2、各个类之间的解耦。
 *      3、符合迪米特原则。
 * 缺点：中介者会庞大，变得复杂难以维护。
 * 使用场景：
 *      1、系统中对象之间存在比较复杂的引用关系，导致它们之间的依赖关系结构混乱而且难以复用该对象。
 *      2、想通过一个中间类来封装多个类中的行为，而又不想生成太多的子类。
 * 注意事项：不应当在职责混乱的时候使用。
*/

#include <iostream>

class Mediator;
//抽象人
class Person {
public:
    virtual void setMediator(Mediator* mediator) {} //设置中介
    virtual void sendMessage(std::string message) {}    //向中介发送信息
    virtual void getMessage(std::string message) {}     //从中介获取信息

    virtual ~Person() = default;

protected:
    Mediator* m_mediator; //中介
};

//抽象中介机构
class Mediator {
public:
    virtual void send(std::string message, Person* person) {}
    virtual void setRenter(Person* A) {}  //设置租户
    virtual void setLandlord(Person* B) {} //设置房东

    virtual ~Mediator() = default;
};

//租房者
class Renter: public Person {
public:
    void setMediator(Mediator* mediator) {
        m_mediator = mediator;
    }

    void sendMessage(std::string message) {
        m_mediator->send(message, this);
    }

    void getMessage(std::string message) {
        std::cout << "renter receive message: " << message << std::endl;
    }
};

//房东
class Landlord: public Person {
public:
    void setMediator(Mediator* mediator) {
        m_mediator = mediator;
    }

    void sendMessage(std::string message) {
        m_mediator->send(message, this);
    }

    void getMessage(std::string message) {
        std::cout << "landlord receive message: " << message << std::endl;
    }
};

//房屋中介
class HouseMediator : public Mediator {
public:
    HouseMediator(): m_renter(0), m_landlord(0) {}

    void setRenter(Person* renter) {
        m_renter = renter;
    }

    void setLandlord(Person* landlord) {
        m_landlord = landlord;
    }

    void send(std::string message, Person* person) {
        if (person == m_renter) { //租房者给房东发信息
            m_landlord->getMessage(message);    //房东收到信息
        } else {
            m_renter->getMessage(message);
        }
    }

private:
    Person* m_renter; //租房者
    Person* m_landlord; //房东
};

//测试案例
int main() {
    Mediator* mediator = new HouseMediator();
    Person* renter = new Renter();    //租房者
    Person* landlord = new Landlord();  //房东
    mediator->setRenter(renter);
    mediator->setLandlord(landlord);
    renter->setMediator(mediator);
    landlord->setMediator(mediator);

    renter->sendMessage("I want rent a house, 800 a month");
    landlord->sendMessage("house 100，70m，1000 a month");

    delete renter;
    delete landlord;
    delete mediator;

    return 0;
}