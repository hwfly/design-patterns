/**
 * 装饰器模式（Decorator Pattern）
 *
 * 意图：动态地给一个对象添加一些额外的职责。就增加功能来说，装饰器模式相比生成子类更为灵活。
 *
 * 主要解决：一般的，我们为了扩展一个类经常使用继承方式实现，由于继承为类引入静态特征，并且随着扩展功能的增多，子类会很膨胀。
 * 何时使用：在不想增加很多子类的情况下扩展类。
 * 如何解决：将具体功能职责划分，同时继承装饰者模式。
 * 关键代码：
 *      1、Component 类充当抽象角色，不应该具体实现。
 *      2、修饰类引用和继承 Component 类，具体扩展类重写父类方法。
 * 应用实例：
 *      1、孙悟空有 72 变，当他变成"庙宇"后，他的根本还是一只猴子，但是他又有了庙宇的功能。
 *      2、不论一幅画有没有画框都可以挂在墙上，但是通常都是有画框的，并且实际上是画框被挂在墙上。在挂在墙上之前，画可以被蒙上玻璃，装到框子里；这时画、玻璃和画框形成了一个物体。
 * 优点：装饰类和被装饰类可以独立发展，不会相互耦合，装饰模式是继承的一个替代模式，装饰模式可以动态扩展一个实现类的功能。
 * 缺点：多层装饰比较复杂。
 * 使用场景：
 *      1、扩展一个类的功能。
 *      2、动态增加功能，动态撤销。
 * 注意事项：可代替继承。
*/

#include <iostream>
#include <memory>

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

class Rectangle: public Shape {
public:
    virtual void draw() override {
        std::cout << "Shape: Rectangle" << std::endl;
    }
};

class Circle: public Shape {
public:
    virtual void draw() override {
        std::cout << "Shape: Circle" << std::endl;
    }
};

class ShapeDecorator: public Shape {
public:
    ShapeDecorator(Shape& decoratedShape) : m_decoratedShape(decoratedShape) {}
    virtual void draw() override {
        m_decoratedShape.draw();
    }

protected:
    Shape& m_decoratedShape;
};

class RedShapeDecorator: public ShapeDecorator {
public:
    RedShapeDecorator(Shape& decoratedShape) : ShapeDecorator(decoratedShape) {}

    virtual void draw() override {
        m_decoratedShape.draw();
        setRedBorder();
    }

    void setRedBorder() {
        std::cout << "Border Color: Red" << std::endl;
    }
};

int main() {
    std::shared_ptr<Shape> circle = std::make_shared<Circle>();
    std::cout << "Circle with normal border" << std::endl;
    circle->draw();

    std::shared_ptr<Shape> redCircle = std::make_shared<RedShapeDecorator>(*circle);
    std::cout << "Circle of red border" << std::endl;
    redCircle->draw();

    std::shared_ptr<Shape> rectangle = std::make_shared<Rectangle>();
    std::cout << "Rectangle with normal border" << std::endl;
    rectangle->draw();

    std::shared_ptr<Shape> redRectangle = std::make_shared<RedShapeDecorator>(*rectangle);
    std::cout << "Rectangle of red border" << std::endl;
    redRectangle->draw();

    return 0;
}