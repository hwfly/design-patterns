/**
 * 访问者模式（Visitor Pattern）
 *
 * 我们使用了一个访问者类，它改变了元素类的执行算法。通过这种方式，元素的执行算法可以随着访问者改变而改变。
 * 这种类型的设计模式属于行为型模式。根据模式，元素对象已接受访问者对象，这样访问者对象就可以处理元素对象上的操作。
 *
 * 意图：主要将数据结构与数据操作分离。
 * 主要解决：稳定的数据结构和易变的操作耦合问题。
 * 何时使用：需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而需要避免让这些操作"污染"这些对象的类，使用访问者模式将这些封装到类中。
 * 如何解决：在被访问的类里面加一个对外提供接待访问者的接口。
 * 关键代码：在数据基础类里面有一个方法接受访问者，将自身引用传入访问者。
 * 应用实例：您在朋友家做客，您是访问者，朋友接受您的访问，您通过朋友的描述，然后对朋友的描述做出一个判断，这就是访问者模式。
 * 优点：
 *      1、符合单一职责原则。
 *      2、优秀的扩展性。
 *      3、灵活性。
 * 缺点：
 *      1、具体元素对访问者公布细节，违反了迪米特原则。
 *      2、具体元素变更比较困难。
 *      3、违反了依赖倒置原则，依赖了具体类，没有依赖抽象。
 * 使用场景：
 *      1、对象结构中对象对应的类很少改变，但经常需要在此对象结构上定义新的操作。
 *      2、需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而需要避免让这些操作"污染"这些对象的类，也不希望在增加新操作时修改这些类。
 * 注意事项：访问者可以对功能进行统一，可以做报表、UI、拦截器与过滤器。
 * 
 * https://blog.csdn.net/liang19890820/article/details/79364406
*/

#include <iostream>
#include <list>

class BellTower;
class TerracottaWarriors;

// 访问者
class Visitor {
public:
    virtual ~Visitor() {}
    virtual void visit(BellTower*) = 0;
    virtual void visit(TerracottaWarriors*) = 0;
};

// 游客
class Tourist : public Visitor {
public:
    virtual void visit(BellTower*) override {
        std::cout << "I'm visiting the Bell Tower!" << std::endl;
    }

    virtual void visit(TerracottaWarriors*) override {
        std::cout << "I'm visiting the Terracotta Warriors!" << std::endl;
    }
};

// 清洁工
class Cleaner : public Visitor {
public:
    virtual void visit(BellTower*) override {
        std::cout << "I'm cleaning up the garbage of Bell Tower!" << std::endl;
    }

    virtual void visit(TerracottaWarriors*) override {
        std::cout << "I'm cleaning up the garbage of Terracotta Warriors!" << std::endl;
    }
};

// 地方
class Place {
public:
    virtual ~Place() {}
    virtual void accept(Visitor* visitor) = 0;
};

// 钟楼
class BellTower : public Place {
public:
    virtual void accept(Visitor* visitor) override {
        std::cout << "Bell Tower is accepting visitor." << std::endl;
        visitor->visit(this);
    }
};

// 兵马俑
class TerracottaWarriors : public Place {
public:
    virtual void accept(Visitor* visitor) override {
        std::cout << "Terracotta Warriors is accepting visitor." << std::endl;
        visitor->visit(this);
    }
};

// 城市（西安）
class City {
public:
    void attach(Place* place) {
        m_places.push_back(place);
    }

    void detach(Place* place) {
        m_places.remove(place);
    }

    void accept(Visitor* visitor) {
        // 为每一个 element 设置 visitor，进行对应的操作
        for (std::list<Place*>::iterator it = m_places.begin(); it != m_places.end(); ++it) {
            (*it)->accept(visitor);
        }
    }

private:
    std::list<Place*> m_places;
};

int main() {
    City* city = new City();

    // 景点 - 钟楼、兵马俑
    Place* bellTower = new BellTower();
    Place* warriors = new TerracottaWarriors();

    // 访问者 - 游客、清洁工
    Visitor* tourist = new Tourist();
    Visitor* cleaner = new Cleaner();

    // 添加景点
    city->attach(bellTower);
    city->attach(warriors);

    // 接受访问
    city->accept(tourist);
    city->accept(cleaner);

    delete cleaner;
    delete tourist;
    delete warriors;
    delete bellTower;
    delete city;

    return 0;
}
