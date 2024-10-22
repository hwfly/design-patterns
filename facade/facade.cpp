/**
 * 外观模式（Facade Pattern）
 *
 * 意图：为子系统中的一组接口提供一个一致的界面，外观模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。
 *
 * 主要解决：降低访问复杂系统的内部子系统时的复杂度，简化客户端与之的接口。
 * 何时使用：
 *      1、客户端不需要知道系统内部的复杂联系，整个系统只需提供一个"接待员"即可。
 *      2、定义系统的入口。
 * 如何解决：客户端不与系统耦合，外观类与系统耦合。
 * 关键代码：在客户端和复杂系统之间再加一层，这一层将调用顺序、依赖关系等处理好。
 * 应用实例：
 *      1、去医院看病，可能要去挂号、门诊、划价、取药，让患者或患者家属觉得很复杂，如果有提供接待人员，只让接待人员来处理，就很方便。
 *      2、JAVA 的三层开发模式。
 * 优点：
 *      1、减少系统相互依赖。
 *      2、提高灵活性。
 *      3、提高了安全性。
 * 缺点：不符合开闭原则，如果要改东西很麻烦，继承重写都不合适。
 * 使用场景：
 *      1、为复杂的模块或子系统提供外界访问的模块。
 *      2、子系统相对独立。
 *      3、预防低水平人员带来的风险。
 * 注意事项：在层次化结构中，可以使用外观模式定义系统中每一层的入口。
*/

#include <iostream>

class Cpu {
public:
    void startup() {
        std::cout << "CPU startup" << std::endl;
    }

    void shutdown() {
        std::cout << "CPU shutdown" << std::endl;
    }
};

class Memory {
public:
    void startup() {
        std::cout << "Memory startup" << std::endl;
    }

    void shutdown() {
        std::cout << "Memory shutdown" << std::endl;
    }
};

class Disk {
public:
    void startup() {
        std::cout << "Disk startup" << std::endl;
    }

    void shutdown() {
        std::cout << "Disk shutdown" << std::endl;
    }
};

class Computer {
public:
    Computer() {}
    void startup() {
        m_cpu.startup();
        m_memory.startup();
        m_disk.startup();
    }

    void shutdown() {
        m_cpu.shutdown();
        m_memory.shutdown();
        m_disk.shutdown();
    }

private:
    Cpu m_cpu;
    Memory m_memory;
    Disk m_disk;
};

int main() {
    Computer computer = Computer();
    computer.startup();
    computer.shutdown();

    return 0;
}