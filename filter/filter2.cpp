/**
 * 过滤器模式（Filter Pattern）或标准模式（Criteria Pattern）是一种设计模式，
 * 这种模式允许开发人员使用不同的标准来过滤一组对象，通过逻辑运算以解耦的方式把它们连接起来。
 * 这种类型的设计模式属于结构型模式，它结合多个标准来获得单一标准
*/

#include <iostream>
#include <algorithm>
#include <list>
#include <memory>

class Person {
public:
    Person(std::string name, std::string gender, std::string maritalStatus) {
        m_name = name;
        m_gender = gender;
        m_maritalStatus = maritalStatus;
    }

    std::string getName() const {
        return m_name;
    }

    std::string getGender() const {
        return m_gender;
    }

    std::string getMaritalStatus() const {
        return m_maritalStatus;
    }

private:
    std::string m_name;
    std::string m_gender;
    std::string m_maritalStatus;
};

using lsp_t = std::list<std::shared_ptr<Person>>;
using slsp_t = std::shared_ptr<std::list<std::shared_ptr<Person>>>;

class Criteria {
public:
    virtual slsp_t meetCriteria(slsp_t persons) = 0;
};

class CriteriaMale: public Criteria {
public:
    virtual slsp_t meetCriteria(slsp_t persons) override {
        slsp_t list = std::make_shared<lsp_t>();

        for (auto it = persons->begin(); it != persons->end(); ++it) {
            if ((*it)->getGender() == "Male") {
                list->push_back(*it);
            }
        }

        return list;
    }
};

class CriteriaFemale: public Criteria {
public:
    virtual slsp_t meetCriteria(slsp_t persons) override {
        slsp_t list = std::make_shared<lsp_t>();

        for (auto it = persons->begin(); it != persons->end(); ++it) {
            if ((*it)->getGender() == "Female") {
                list->push_back(*it);
            }
        }

        return list;
    }
};

class CriteriaSingle: public Criteria {
public:
    virtual slsp_t meetCriteria(slsp_t persons) override {
        slsp_t list = std::make_shared<lsp_t>();

        for (auto it = persons->begin(); it != persons->end(); ++it) {
            if ((*it)->getMaritalStatus() == "Single") {
                list->push_back(*it);
            }
        }

        return list;
    }
};

class AndCriteria: public Criteria {
public:
    virtual slsp_t meetCriteria(slsp_t persons) override {
        slsp_t firstCriteriaPersons = m_criteria->meetCriteria(persons);
        return m_otherCriteria->meetCriteria(firstCriteriaPersons);
    }

    AndCriteria(std::shared_ptr<Criteria> criteria, std::shared_ptr<Criteria> otherCriteria) {
        m_criteria = criteria;
        m_otherCriteria = otherCriteria;
    }

private:
    std::shared_ptr<Criteria> m_criteria;
    std::shared_ptr<Criteria> m_otherCriteria;
};

class OrCriteria: public Criteria {
public:
    virtual slsp_t meetCriteria(slsp_t persons) override {
        slsp_t firstCriteriaPersons = m_criteria->meetCriteria(persons);
        slsp_t otherCriteriaPersons = m_otherCriteria->meetCriteria(persons);

        for (auto person : *otherCriteriaPersons) {
            if (std::find_if((*firstCriteriaPersons).begin(), (*firstCriteriaPersons).end(),
            [person](std::shared_ptr<Person> p) {
            return person->getName() == p->getName();
            }) == (*firstCriteriaPersons).end()) {
                (*firstCriteriaPersons).push_back(person);
            }
        }

        return firstCriteriaPersons;
    }

    OrCriteria(std::shared_ptr<Criteria> criteria, std::shared_ptr<Criteria> otherCriteria) {
        m_criteria = criteria;
        m_otherCriteria = otherCriteria;
    }

private:
    std::shared_ptr<Criteria> m_criteria;
    std::shared_ptr<Criteria> m_otherCriteria;
};

void printPersons(slsp_t persons) {
    for (auto it = persons->begin(); it != persons->end(); ++it) {
        std::cout << "Person : [ Name : " << (*it)->getName() << ", Gender : " <<
                  (*it)->getGender() << ", Marital Status : " << (*it)->getMaritalStatus() << " ]" << std::endl;
    }

}

int main() {
    slsp_t persons = std::make_shared<lsp_t>();
    persons->push_back(std::shared_ptr<Person>(new Person("Robert", "Male", "Single")));
    persons->push_back(std::shared_ptr<Person>(new Person("John", "Male", "Married")));
    persons->push_back(std::shared_ptr<Person>(new Person("Laura", "Female", "Married")));
    persons->push_back(std::shared_ptr<Person>(new Person("Diana", "Female", "Single")));
    persons->push_back(std::shared_ptr<Person>(new Person("Mike", "Male", "Single")));
    persons->push_back(std::shared_ptr<Person>(new Person("Bobby", "Male", "Single")));

    printPersons(persons);

    std::shared_ptr<CriteriaMale> male(new CriteriaMale());
    std::shared_ptr<CriteriaFemale> female(new CriteriaFemale());
    std::shared_ptr<CriteriaSingle> single(new CriteriaSingle());
    std::shared_ptr<AndCriteria> singleMale(new AndCriteria(single, male));
    std::shared_ptr<OrCriteria> singleOrFemale(new OrCriteria(single, female));

    std::cout << "\nMale:" << std::endl;
    printPersons(male->meetCriteria(persons));

    std::cout << "\nFemale:" << std::endl;
    printPersons(female->meetCriteria(persons));

    std::cout << "\nSingle:" << std::endl;
    printPersons(single->meetCriteria(persons));

    std::cout << "\nSingle Male:" << std::endl;
    printPersons(singleMale->meetCriteria(persons));

    std::cout << "\nSingle Or Female:" << std::endl;
    printPersons(singleOrFemale->meetCriteria(persons));

    return 0;
}