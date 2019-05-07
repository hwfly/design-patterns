/**
 * 建造者模式
 * 
 * 将复杂对象的构建和其表示分离，使得同样的构建过程可以创建不同的表示。
 * 
 * 主要解决：一个复杂对象的创建工作，由各个部分的子对象用一定的算法构成；由于需求变化，这个复杂对象的各个部分经常面临变化，但将它们组合在一起的算法却相对稳定。
 * 如何解决：将变与不变分开
 * 关键代码：建造者：创建和提供实例，Director：管理建造出来的实例的依赖关系。。
 * 缺点：1、产品必须有共同点，范围有限制。 2、如内部变化复杂，会有很多的建造类。
*/

#include <iostream>

//product 产品类
class Bike {
public:
    std::string getFrame() const {
        return m_frame;
    }

    void setFrame(std::string frame) {
        m_frame = frame;
    }

    std::string getSeat() const {
        return m_seat;
    }

    void setSeat(std::string seat) {
        m_seat = seat;
    }

    std::string getTire() const {
        return m_tire;
    }

    void setTire(std::string tire) {
        m_tire = tire;
    }

private:
    std::string m_frame;
    std::string m_seat;
    std::string m_tire;
};

//builder 抽象建造者类
class Builder {
public:
    virtual void buildFrame() = 0;
    virtual void buildSeat() = 0;
    virtual void buildTire() = 0;
    virtual void createBike() = 0;
    virtual Bike* getBike() = 0;

    virtual ~Builder() = default;
};

//ConcreteBuilder 具体建造者类
class MobikeBuilder: public Builder {
public:
    virtual void buildFrame() override {
        m_bike->setFrame("AlloyFrame");
    }

    virtual void buildSeat() override {
        m_bike->setSeat("DermisSeat");
    }

    virtual void buildTire() override {
        m_bike->setTire("SolidTire");
    }

    virtual void createBike() override {
        m_bike = new Bike();
    }

    virtual Bike* getBike() override {
        return m_bike;
    }

private:
    Bike* m_bike;
};

class OfoBuilder: public Builder {
public:
    virtual void buildFrame() override {
        m_bike->setFrame("CarbonFrame");
    }

    virtual void buildSeat() override {
        m_bike->setSeat("RubberSeat");
    }

    virtual void buildTire() override {
        m_bike->setTire("InflateTire");
    }

    virtual void createBike() override {
        m_bike = new Bike();
    }

    virtual Bike* getBike() override {
        return m_bike;
    }

private:
    Bike* m_bike;
};

//Director 指挥者类
class Director {
public:
    Director(Builder* builder) {
        m_builder = builder;
    }

    Bike* construct() {
        m_builder->createBike();
        m_builder->buildFrame();
        m_builder->buildSeat();
        m_builder->buildTire();
        return m_builder->getBike();
    }

private:
    Builder* m_builder;
};

int main() {
    std::cout << "Mobike :" << std::endl;
    Builder* builer = new MobikeBuilder();
    Director* director = new Director(builer);
    Bike* bike = director->construct();
    std::cout << bike->getFrame() << " " << bike->getSeat() << " " << bike->getTire() << std::endl;
    delete builer;
    delete director;

    std::cout << "ofo :" << std::endl;
    builer = new OfoBuilder();
    director = new Director(builer);
    bike = director->construct();
    std::cout << bike->getFrame() << " " << bike->getSeat() << " " << bike->getTire() << std::endl;
    delete builer;
    delete director;

    return 0;
}