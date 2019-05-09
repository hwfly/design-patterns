/**
 * 组合模式（Composite Pattern），又叫部分整体模式
 *
 * 是用于把一组相似的对象当作一个单一的对象。组合模式依据树形结构来组合对象，用来表示部分以及整体层次。
 * 这种类型的设计模式属于结构型模式，它创建了对象组的树形结构。这种模式创建了一个包含自己对象组的类。该类提供了修改相同对象组的方式。
 * 我们通过下面的实例来演示组合模式的用法。实例演示了一个组织中员工的层次结构。
 *
 * 意图：将对象组合成树形结构以表示"部分-整体"的层次结构。组合模式使得用户对单个对象和组合对象的使用具有一致性。
 *
 * 主要解决：它在我们树型结构的问题中，模糊了简单元素和复杂元素的概念，客户程序可以向处理简单元素一样来处理复杂元素，从而使得客户程序与复杂元素的内部结构解耦。
 * 何时使用：
 *      1、您想表示对象的部分-整体层次结构（树形结构）。
 *      2、您希望用户忽略组合对象与单个对象的不同，用户将统一地使用组合结构中的所有对象。
 * 如何解决：树枝和叶子实现统一接口，树枝内部组合该接口。
 * 关键代码：树枝内部组合该接口，并且含有内部属性 List，里面放 Component。
 * 应用实例：
 *      1、算术表达式包括操作数、操作符和另一个操作数，其中，另一个操作符也可以是操作数、操作符和另一个操作数。
 *      2、在 JAVA AWT 和 SWING 中，对于 Button 和 Checkbox 是树叶，Container 是树枝。
 * 优点：
 *      1、高层模块调用简单。
 *      2、节点自由增加。
 * 缺点：在使用组合模式时，其叶子和树枝的声明都是实现类，而不是接口，违反了依赖倒置原则。
 * 使用场景：部分、整体场景，如树形菜单，文件、文件夹的管理。
 * 注意事项：定义时为具体类。
*/

#include <iostream>
#include <memory>
#include <list>

class Employee {
public:
    Employee(std::string name, std::string dept, int salary) {
        m_name = name;
        m_dept = dept;
        m_salary = salary;
    }

    void add(std::shared_ptr<Employee> e) {
        m_subordinates.push_back(e);
    }

    void remove(std::shared_ptr<Employee> e) {
        m_subordinates.remove(e);
    }

    std::list<std::shared_ptr<Employee>> getSubordinates() {
        return m_subordinates;
    }

    bool operator==(const Employee& e) {
        return (m_name == e.m_name) && (m_dept == e.m_dept) && (m_salary == e.m_salary);
    }

    friend std::ostream& operator<<(std::ostream& os, const Employee& e);

private:
    std::string m_name;
    std::string m_dept;
    int m_salary;

    std::list<std::shared_ptr<Employee>> m_subordinates;
};

std::ostream& operator<<(std::ostream& os, const Employee& e) {
    os << "Employee :[ Name : " << e.m_name << ", dept : " << e.m_dept << ", salary :" << e.m_salary <<
       " ]";
    return os;
}

int main() {
    std::shared_ptr<Employee> CEO = std::make_shared<Employee>("John", "CEO", 30000);

    std::shared_ptr<Employee> headSales = std::make_shared<Employee>("Robert", "Head Sales", 20000);

    std::shared_ptr<Employee> headMarketing = std::make_shared<Employee>("Michel", "Head Marketing",
            20000);

    std::shared_ptr<Employee> clerk1 = std::make_shared<Employee>("Laura", "Marketing", 10000);
    std::shared_ptr<Employee> clerk2 = std::make_shared<Employee>("Bob", "Marketing", 10000);

    std::shared_ptr<Employee> salesExecutive1 = std::make_shared<Employee>("Richard", "Sales", 10000);
    std::shared_ptr<Employee> salesExecutive2 = std::make_shared<Employee>("Rob", "Sales", 10000);

    CEO->add(headSales);
    CEO->add(headMarketing);

    headSales->add(salesExecutive1);
    headSales->add(salesExecutive2);

    headMarketing->add(clerk1);
    headMarketing->add(clerk2);

    //打印该组织的所有员工
    std::cout << *CEO << std::endl;

    for (auto headEmployee : CEO->getSubordinates()) {
        std::cout << *headEmployee << std::endl;

        for (auto employee : headEmployee->getSubordinates()) {
            std::cout << *employee << std::endl;
        }
    }

    return 0;
}