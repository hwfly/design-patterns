/**
 * 迭代器模式（Iterator Pattern）
 *
 * 意图：提供一种方法顺序访问一个聚合对象中各个元素, 而又无须暴露该对象的内部表示。
 * 主要解决：不同的方式来遍历整个整合对象。
 * 何时使用：遍历一个聚合对象。
 * 如何解决：把在元素之间游走的责任交给迭代器，而不是聚合对象。
 * 关键代码：定义接口：hasNext, next。
 * 优点：
 *      1、它支持以不同的方式遍历一个聚合对象。
 *      2、迭代器简化了聚合类。
 *      3、在同一个聚合上可以有多个遍历。
 *      4、在迭代器模式中，增加新的聚合类和迭代器类都很方便，无须修改原有代码。
 * 缺点：由于迭代器模式将存储数据和遍历数据的职责分离，增加新的聚合类需要对应增加新的迭代器类，类的个数成对增加，这在一定程度上增加了系统的复杂性。
 * 使用场景：
 *      1、访问一个聚合对象的内容而无须暴露它的内部表示。
 *      2、需要为聚合对象提供多种遍历方式。
 *      3、为遍历不同的聚合结构提供一个统一的接口。
 * 注意事项：迭代器模式就是分离了集合对象的遍历行为，抽象出一个迭代器类来负责，这样既可以做到不暴露集合的内部结构，又可让外部代码透明地访问集合内部的数据。
*/

#include <iostream>

class Iterator {
public:
    Iterator() = default;
    virtual ~Iterator() = default;

    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual int currentItem() = 0;
};

class Aggregate {
public:
    virtual ~Aggregate() {}

    virtual Iterator* createIterater() = 0;
    virtual int getSize() = 0;
    virtual int getItem(int nIndex) = 0;
};

// 访问ConcreateAggregate容器类的迭代器类
class ConcreateIterater: public Iterator {
public:
    ConcreateIterater(Aggregate* pAggregate) : m_pConcreateAggregate(pAggregate), m_nIndex(0) {}

    virtual ~ConcreateIterater() {}

    virtual void first() {
        m_nIndex = 0;
    }

    virtual void next() {
        if (m_nIndex < m_pConcreateAggregate->getSize()) {
            ++m_nIndex;
        }
    }

    virtual bool isDone() {
        return m_nIndex == m_pConcreateAggregate->getSize();
    }

    virtual int currentItem() {
        return m_pConcreateAggregate->getItem(m_nIndex);
    }

private:
    Aggregate* m_pConcreateAggregate;
    int m_nIndex;
};

// 一个具体的容器类,这里是用数组表示
class ConcreateAggregate: public Aggregate {
public:
    ConcreateAggregate(int nSize) : m_nSize(nSize), m_pData(nullptr) {
        m_pData = new int[m_nSize];

        for (int i = 0; i < nSize; ++i) {
            m_pData[i] = i;
        }
    }

    virtual ~ConcreateAggregate() {
        delete [] m_pData;
        m_pData = NULL;
    }

    virtual Iterator* createIterater() override {
        return new ConcreateIterater(this);
    }

    virtual int getSize() override {
        return m_nSize;
    }

    virtual int getItem(int nIndex) override {
        if (nIndex < m_nSize) {
            return m_pData[nIndex];
        } else {
            return -1;
        }
    }

private:
    int m_nSize;
    int* m_pData;
};

int main() {
    Aggregate* pAggregate = new ConcreateAggregate(4);
    Iterator* pIterator = pAggregate->createIterater();

    for (pIterator->first(); !pIterator->isDone(); pIterator->next()) {
        std::cout << pIterator->currentItem() << std::endl;
    }

    delete pAggregate;
    delete pIterator;

    return 0;
}