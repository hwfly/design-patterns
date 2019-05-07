/**
 * 原型模式
 *
 * 用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
 *
 * 主要解决：在运行期建立和删除对象。
 * 何时使用：
 *      1).当我们的对象类型不是开始就能确定的，而这个类型是在运行期确定的话，那么我们通过这个类型的对象克隆出一个新的对象比较容易一些；
 *      2).有的时候，我们需要一个对象在某个状态下的副本，此时，我们使用原型模式是最好的选择；例如：一个对象，经过一段处理之后，其内部的状态发生了变化；这个时候，我们需要一个这个状态的副本，如果直接new一个新的对象的话,但是它的状态是不对的，此时，可以使用原型模式，将原来的对象拷贝一个出来，这个对象就和之前的对象是完全一致的了；
 *      3).当我们处理一些比较简单的对象时，并且对象之间的区别很小，可能就几个属性不同而已，那么就可以使用原型模式来完成，省去了创建对象时的麻烦了；
 *      4).有的时候，创建对象时，构造函数的参数很多，而自己又不完全的知道每个参数的意义，就可以使用原型模式来创建一个新的对象，不必去理会创建的过程。
 *
 * ->适当的时候考虑一下原型模式，能减少对应的工作量，减少程序的复杂度，提高效率
 * 如何解决：利用已有的一个原型对象，快速地生成和原型对象一样的实例。
 * 关键代码：拷贝，return new className(*this);
*/

#include <iostream>

class Clone {
public:
    Clone() {}
    virtual ~Clone() {}
    virtual Clone* clone() = 0;
    virtual void show() = 0;
};

class Sheep: public Clone {
public:
    Sheep(int id, std::string name): Clone(), m_id(id), m_name(name) {
        std::cout << "Sheep() id add:" << &m_id << std::endl;
        std::cout << "Sheep() name add:" << &m_name << std::endl;
    }
    ~Sheep() {
    }

    Sheep(const Sheep& obj) {
        this->m_id = obj.m_id;
        this->m_name = obj.m_name;
        std::cout << "Sheep(const Sheep& obj) id add:" << &m_id << std::endl;
        std::cout << "Sheep(const Sheep& obj) name add:" << &m_name << std::endl;
    }

    Clone* clone() override {
        return new Sheep(*this);
    }
    void show() override {
        std::cout << "id  :" << m_id << std::endl;
        std::cout << "name:" << m_name.data() << std::endl;
    }
private:
    int m_id;
    std::string m_name;
};

int main() {
    Clone* s1 = new Sheep(1, "abs");
    s1->show();
    Clone* s2 = s1->clone();
    s2->show();
    delete s1;
    delete s2;

    return 0;
}