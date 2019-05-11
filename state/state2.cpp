/**
 * https://blog.csdn.net/yongh701/article/details/49154439
*/

#include<iostream>

//以下为类的定义部分
class TissueMachine;//类的提前引用

//抽象状态
class State {
public:
    virtual void insertQuarter() = 0; //“投币”按钮被按下
    virtual void ejectQuarter() = 0; //“退币”按钮被按下
    virtual void turnCrank() = 0; //“出纸巾”按钮被按下
    virtual void dispense() = 0; //正在卖出纸巾
};

//具体状态
class SoldOutState: public State { //纸巾售完状态
public:
    SoldOutState(TissueMachine* tissueMachine) {
        this->tissueMachine = tissueMachine;
    }

    void insertQuarter();
    void ejectQuarter();
    void turnCrank();
    void dispense();

private:
    TissueMachine* tissueMachine;
};

class NoQuarterState: public State { //没有投币状态
public:
    NoQuarterState(TissueMachine* tissueMachine) {
        this->tissueMachine = tissueMachine;
    }

    void insertQuarter();
    void ejectQuarter();
    void turnCrank();
    void dispense();

private:
    TissueMachine* tissueMachine;
};

class HasQuarterState: public State { //有2元钱（已投币状态）
public:
    HasQuarterState(TissueMachine* tissueMachine) {
        this->tissueMachine = tissueMachine;
    }

    void insertQuarter();
    void ejectQuarter();
    void turnCrank();
    void dispense();

private:
    TissueMachine* tissueMachine;
};

class SoldState: public State { //出售纸巾状态
public:
    SoldState(TissueMachine* tissueMachine) {
        this->tissueMachine = tissueMachine;
    }

    void insertQuarter();
    void ejectQuarter();
    void turnCrank();
    void dispense();

private:
    TissueMachine* tissueMachine;
};

//上下文
class TissueMachine {
public:
    TissueMachine(int numbers) { //构造函数，定义初始状态有纸巾售卖机有多少纸巾
        soldOutState = new SoldOutState(this);
        noQuarterState = new NoQuarterState(this);
        hasQuarterState = new HasQuarterState(this);
        soldState = new SoldState(this);
        this->count = numbers;

        if (count > 0) {
            this->state = noQuarterState; //开始为没有投币的状态
        }
    };

    //开放给主函数调用的方法
    void insertQuarter() {
        state->insertQuarter();
    }

    void ejectQuarter() {
        state->ejectQuarter();
    }

    void turnCrank() {
        state->turnCrank();
        state->dispense();
    }

    //数据传递的getter与setter
    void setState(State* state) {
        this->state = state;
    }

    State* getHasQuarterState() {
        return hasQuarterState;
    }

    State* getNoQuarterState() {
        return noQuarterState;
    }

    State* getSoldState() {
        return soldState;
    }

    State* getSoldOutState() {
        return soldOutState;
    }

    int getCount() {
        return count;
    };

    void setCount(int numbers) {
        this->count = numbers;
    };

private:
    State* soldOutState, *noQuarterState, *hasQuarterState, *soldState, *state;
    int count;//纸巾数
};

//具体状态中各个方法的具体实现。
//纸巾售完状态
void SoldOutState::insertQuarter() {
    std::cout << "机器无纸巾，已退回硬币！" << std::endl;
}

void SoldOutState::ejectQuarter() {
    std::cout << "自动售货机根本没有硬币！" << std::endl;
}

void SoldOutState::turnCrank() {
    std::cout << "机器无纸巾，请不要操作机器" << std::endl;
}

void SoldOutState::dispense() {
}

//没有投币状态
void NoQuarterState::insertQuarter() {
    tissueMachine->setState(tissueMachine->getHasQuarterState());
    std::cout << "已投币！" << std::endl;
}

void NoQuarterState::ejectQuarter() {
    std::cout << "自动售货机根本没有硬币！" << std::endl;
}

void NoQuarterState::turnCrank() {
    std::cout << "请投币" << std::endl;
}

void NoQuarterState::dispense() {
}

//有2元钱（已投币状态）
void HasQuarterState::insertQuarter() {
    std::cout << "已投币！请不要重复投币！已退回重复投币！" << std::endl;
}

void HasQuarterState::ejectQuarter() {
    tissueMachine->setState(tissueMachine->getNoQuarterState());
    std::cout << "已取币！" << std::endl;
}

void HasQuarterState::turnCrank() {
    tissueMachine->setState(tissueMachine->getSoldState());
    std::cout << "请等待自动售货机出纸巾！" << std::endl;
}

void HasQuarterState::dispense() {
}

//出售纸巾状态
void SoldState::insertQuarter() {
    std::cout << "请等待自动售货机出纸巾！请不要投币！已退回投币！" <<
              std::endl;
}

void SoldState::ejectQuarter() {
    tissueMachine->setState(tissueMachine->getNoQuarterState());
    std::cout << "请等待自动售货机出纸巾！无法取回已消费的硬币！" << std::endl;
}

void SoldState::turnCrank() {
    std::cout << "请等待自动售货机出纸巾！已响应你的操作！" << std::endl;
}

void SoldState::dispense() { //售出纸巾动作
    if (tissueMachine->getCount() > 0) {
        tissueMachine->setState(tissueMachine->getNoQuarterState());
        tissueMachine->setCount(tissueMachine->getCount() - 1);
        std::cout << "你的纸巾，请拿好！" << std::endl;
    } else {
        tissueMachine->setState(tissueMachine->getSoldOutState());
        std::cout << "已退回你的硬币！纸巾已卖光，等待进货！" << std::endl;
    }
}

//主函数
int main() {
    TissueMachine* tissueMachine = new TissueMachine(1);
    std::cout << "纸巾数：" << tissueMachine->getCount() << std::endl;
    tissueMachine->insertQuarter();//投币
    tissueMachine->turnCrank();//取纸巾
    std::cout << "纸巾数：" << tissueMachine->getCount() << std::endl; //不投币取纸巾测试
    tissueMachine->turnCrank();
    std::cout << "纸巾数：" << tissueMachine->getCount() <<
              std::endl; //售完纸巾，投币取纸巾测试
    tissueMachine->insertQuarter();
    tissueMachine->turnCrank();
    return 0;
}