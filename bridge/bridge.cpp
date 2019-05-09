/**
 * 桥接模式
 *
 * 将抽象部分与实现部分分离，使它们都可以独立的变化。
 *
 * 主要解决：在有多种可能会变化的情况下，用继承会造成类爆炸问题，扩展起来不灵活。
 * 何时使用：实现系统可能有多个角度分类，每一种角度都可能变化。
 * 如何解决：把这种多角度分类分离出来，让它们独立变化，减少它们之间耦合。
 * 关键代码：抽象类依赖实现类。
 * 另外例子：https://www.cnblogs.com/lixiuyu/p/5923160.html
*/

#include <iostream>
#include <memory>

class DrawAPI {
public:
    virtual void drawCircle(int radius, int x, int y) = 0;
    virtual ~DrawAPI() = default;
};

class RedCircle: public DrawAPI {
public:
    void drawCircle(int radius, int x, int y) override {
        std::cout << "Drawing Circle[ color: red, radius: " << radius << ", x: " << x << ", y: " << y << "]"
                  << std::endl;
    }
};

class GreenCircle: public DrawAPI {
public:
    void drawCircle(int radius, int x, int y) override {
        std::cout << "Drawing Circle[ color: green, radius: " << radius << ", x: " << x << ", y: " << y <<
                  "]" << std::endl;
    }
};

class Shape {
public:
    virtual void draw() = 0;

    virtual ~Shape() = default;

protected:
    std::shared_ptr<DrawAPI> m_drawAPI;
    Shape(std::shared_ptr<DrawAPI> drawAPI) {
        m_drawAPI = drawAPI;
    }
};

class Circle: public Shape {
public:
    Circle(int x, int y, int radius, std::shared_ptr<DrawAPI> drawAPI) : Shape(drawAPI) {
        m_x = x;
        m_y = y;
        m_radius = radius;
    }

    virtual void draw() override {
        m_drawAPI->drawCircle(m_radius, m_x, m_y);
    }

private:
    int m_x;
    int m_y;
    int m_radius;
};

int main() {
    std::shared_ptr<RedCircle> redCircle(new RedCircle());
    std::shared_ptr<Shape> shape = std::shared_ptr<Shape>(new Circle(100, 100, 10, redCircle));
    shape->draw();

    std::shared_ptr<GreenCircle> greenCircle(new GreenCircle());
    shape = std::shared_ptr<Shape>(new Circle(100, 100, 10, greenCircle));
    shape->draw();

    return 0;
}

/**
 * 桥接模式中，具体的实现类放在作为“桥梁”的接口中实现，而“桥梁”接口中只有实现功能的抽象方法；
 * 具体实现类是继承“桥梁”，而不直接继承实现类的抽象类，抽象类与具体的实现类在结构上是相互独立的，
 * 两者的相互变化并不会影响到彼此，只要“桥梁”没变，两者的变化并不会影响到彼此。
 * 就以上教程的实例程序来说，具体的实现是RedCircle、GreenCircle，它们的抽象类为Shape，
 * 按一般逻辑来说，我们是直接继承Shape来创建不同的具体对象，但桥接模式中是通过“桥梁”DrawAPI建立抽象与具体实现之间的联系，
 * 调用DrawAPI中的方法来具体实现。
*/