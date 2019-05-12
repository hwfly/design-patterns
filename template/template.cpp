/**
 * 模板模式（Template Pattern）
 *
 * 意图：定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。
 * 主要解决：一些方法通用，却在每一个子类都重新写了这一方法。
 * 何时使用：有一些通用的方法。
 * 如何解决：将这些通用算法抽象出来。
 * 关键代码：在抽象类实现，其他步骤在子类实现。
 * 应用实例：
 *      1、在造房子的时候，地基、走线、水管都一样，只有在建筑的后期才有加壁橱加栅栏等差异。
 *      2、西游记里面菩萨定好的 81 难，这就是一个顶层的逻辑骨架。
 * 优点：
 *      1、封装不变部分，扩展可变部分。
 *      2、提取公共代码，便于维护。
 *      3、行为由父类控制，子类实现。
 * 缺点：每一个不同的实现都需要一个子类来实现，导致类的个数增加，使得系统更加庞大。
 * 使用场景：
 *      1、有多个子类共有的方法，且逻辑相同。
 *      2、重要的、复杂的方法，可以考虑作为模板方法。
 * 注意事项：为防止恶意操作，一般模板方法都加上 final 关键词。
*/

#include <iostream>

class Game {
public:
    virtual ~Game() = default;

    void play() {
        //初始化游戏
        initialize();

        //开始游戏
        startPlay();

        //结束游戏
        endPlay();
    }

private:
    virtual void initialize() = 0;
    virtual void startPlay() = 0;
    virtual void endPlay() = 0;
};

class Cricket: public Game {
public:
    virtual void initialize() override {
        std::cout << "Cricket Game Initialized! Start playing." << std::endl;
    }

    virtual void startPlay() override {
        std::cout << "Cricket Game Started. Enjoy the game!" << std::endl;
    }

    virtual void endPlay() override {
        std::cout << "Cricket Game Finished!" << std::endl;
    }
};

class Football: public Game {
public:
    virtual void initialize() override {
        std::cout << "Football Game Initialized! Start playing." << std::endl;
    }

    virtual void startPlay() override {
        std::cout << "Football Game Started. Enjoy the game!" << std::endl;
    }

    virtual void endPlay() override {
        std::cout << "Football Game Finished!" << std::endl;
    }
};

int main() {
    Game* game = new Cricket();
    game->play();
    delete game;

    game = new Football();
    game->play();
    delete game;

    return 0;
}