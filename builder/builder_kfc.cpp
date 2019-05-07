#include <iostream>
#include <memory>
#include <list>

class Packing {
public:
    virtual std::string pack() = 0;
    virtual ~Packing() = default;
};

class Wrapper: public Packing {
public:
    virtual std::string pack() override {
        return "Wrapper";
    }
};

class Bottle: public Packing {
public:
    virtual std::string pack() override {
        return "Bottle";
    }
};

class Item {
public:
    virtual std::string name() = 0;
    virtual std::shared_ptr<Packing> packing() = 0;
    virtual float price() = 0;
    virtual ~Item() = default;
};

class Burger: public Item {
public:
    virtual std::shared_ptr<Packing> packing() override {
        return std::shared_ptr<Packing>(new Wrapper());
    }
    virtual std::string name() = 0;
    virtual float price() = 0;
};

class ColdDrink: public Item {
public:
    virtual std::shared_ptr<Packing> packing() override {
        return std::shared_ptr<Packing>(new Bottle());
    }
    virtual std::string name() = 0;
    virtual float price() = 0;
};

class VegBurger: public Burger {
    virtual float price() override {
        return 25.0f;
    }

    virtual std::string name() override {
        return "Veg Burger";
    }
};

class ChickenBurger: public Burger {
    virtual float price() override {
        return 50.5f;
    }

    virtual std::string name() override {
        return "Chicken Burger";
    }
};

class Coke: public ColdDrink {
    virtual float price() override {
        return 30.0f;
    }

    virtual std::string name() override {
        return "Coke";
    }
};

class Pepsi: public ColdDrink {
    virtual float price() override {
        return 35.0f;
    }

    virtual std::string name() override {
        return "Pepsi";
    }
};


class Meal {
public:
    void addItem(std::shared_ptr<Item> item) {
        items.push_back(item);
    }

    float getCost() {
        float cost = 0.0f;

        for (auto item : items) {
            cost += item->price();
        }

        return cost;
    }

    void showItems() {
        for (auto item : items) {
            std::cout << "Item : " << item->name();
            std::cout << ", Packing : " << item->packing()->pack();
            std::cout << ", Price : " << item->price() << std::endl;
        }
    }
private:
    std::list<std::shared_ptr<Item>> items;
};

class MealBuilder {
public:
    std::shared_ptr<Meal> prepareVegMeal() {
        std::shared_ptr<Meal> meal(new Meal());
        std::shared_ptr<VegBurger> vegBurger(new VegBurger());
        meal->addItem(vegBurger);
        std::shared_ptr<Coke> coke(new Coke());
        meal->addItem(coke);
        return meal;
    }

    std::shared_ptr<Meal> prepareNonVegMeal() {
        std::shared_ptr<Meal> meal(new Meal());
        std::shared_ptr<ChickenBurger> chickenBurger(new ChickenBurger());
        meal->addItem(chickenBurger);
        std::shared_ptr<Pepsi> pepsi(new Pepsi());
        meal->addItem(pepsi);
        return meal;
    }
};

int main() {
    std::shared_ptr<MealBuilder> mealBuilder(new MealBuilder());

    std::shared_ptr<Meal> vegMeal = mealBuilder->prepareVegMeal();
    std::cout << "Veg Meal" << std::endl;
    vegMeal->showItems();
    std::cout << "Total Cost: " << vegMeal->getCost() << std::endl;;

    std::shared_ptr<Meal> nonVegMeal = mealBuilder->prepareNonVegMeal();
    std::cout << "\n\nNon-Veg Meal" << std::endl;
    nonVegMeal->showItems();
    std::cout << "Total Cost: "  << nonVegMeal->getCost() << std::endl;

    return 0;
}