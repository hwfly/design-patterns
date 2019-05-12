/**
 * 空对象模式（Null Object Pattern）
 *
 * 一个空对象取代 NULL 对象实例的检查。Null 对象不是检查空值，而是反应一个不做任何动作的关系。
 * 这样的 Null 对象也可以在数据不可用的时候提供默认的行为。在空对象模式中，我们创建一个指定各种要执行的操作的抽象类和扩展该类的实体类，
 * 还创建一个未对该类做任何实现的空对象类，该空对象类将无缝地使用在需要检查空值的地方。
*/

#include <iostream>
#include <memory>
#include <vector>

class AbstractCustomer {
public:
    AbstractCustomer(std::string name) : m_nmae(name) {}
    virtual ~AbstractCustomer() = default;

    virtual bool isNil() = 0;
    virtual std::string getName() = 0;

protected:
    std::string m_nmae;
};

class RealCustomer: public AbstractCustomer {
public:
    RealCustomer(std::string name) : AbstractCustomer(name) {}

    virtual bool isNil() override {
        return false;
    }

    virtual std::string getName() override {
        return m_nmae;
    }
};

class NullCustomer: public AbstractCustomer {
public:
    NullCustomer() : AbstractCustomer("") {}

    virtual bool isNil() override {
        return true;
    }

    virtual std::string getName() override {
        return "Not Available in Customer Database";
    }
};

class CustomerFactory {
public:
    static const std::vector<std::string> names;

    static std::shared_ptr<AbstractCustomer> getCustomer(std::string name) {
        for (auto nm : names) {
            if (nm == name) {
                return std::make_shared<RealCustomer>(name);
            }
        }

        return std::make_shared<NullCustomer>();
    }
};

const std::vector<std::string> CustomerFactory::names = {"Rob", "Joe", "Julie"};

int main() {
    std::shared_ptr<AbstractCustomer>  customer1 = CustomerFactory::getCustomer("Rob");
    std::shared_ptr<AbstractCustomer>  customer2 = CustomerFactory::getCustomer("Bob");
    std::shared_ptr<AbstractCustomer>  customer3 = CustomerFactory::getCustomer("Julie");
    std::shared_ptr<AbstractCustomer>  customer4 = CustomerFactory::getCustomer("Laura");

    std::cout << "Customers" << std::endl;
    std::cout << customer1->getName() << std::endl;
    std::cout << customer2->getName() << std::endl;
    std::cout << customer3->getName() << std::endl;
    std::cout << customer4->getName() << std::endl;

    return 0;
}