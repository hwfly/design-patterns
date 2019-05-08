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

class Criteria {
public:
    virtual std::list<Person> meetCriteria(std::list<Person> persons) = 0;
};

class CriteriaMale: public Criteria {
public:
    virtual std::list<Person> meetCriteria(std::list<Person> persons) override {
        m_list.clear();

        for (auto person : persons) {
            if (person.getGender() == "Male") {
                m_list.push_back(person);
            }
        }

        return m_list;
    }
private:
    std::list<Person> m_list;
};

class CriteriaFemale: public Criteria {
public:
    virtual std::list<Person> meetCriteria(std::list<Person> persons) override {
        m_list.clear();

        for (auto person : persons) {
            if (person.getGender() == "Female") {
                m_list.push_back(person);
            }
        }

        return m_list;
    }
private:
    std::list<Person> m_list;
};

class CriteriaSingle: public Criteria {
public:
    virtual std::list<Person> meetCriteria(std::list<Person> persons) override {
        m_list.clear();

        for (auto person : persons) {
            if (person.getMaritalStatus() == "Single") {
                m_list.push_back(person);
            }
        }

        return m_list;
    }
private:
    std::list<Person> m_list;
};

class AndCriteria: public Criteria {
public:
    virtual std::list<Person> meetCriteria(std::list<Person> persons) override {
        std::list<Person> firstCriteriaPersons = m_criteria.meetCriteria(persons);
        return m_otherCriteria.meetCriteria(firstCriteriaPersons);
    }

    AndCriteria(Criteria& criteria, Criteria& otherCriteria) : m_criteria(criteria),
        m_otherCriteria(otherCriteria) {}

private:
    Criteria& m_criteria;
    Criteria& m_otherCriteria;
};

class OrCriteria: public Criteria {
public:
    virtual std::list<Person> meetCriteria(std::list<Person> persons) override {
        std::list<Person> firstCriteriaPersons = m_criteria.meetCriteria(persons);
        std::list<Person> otherCriteriaPersons = m_otherCriteria.meetCriteria(persons);

        for (auto person : otherCriteriaPersons) {
            if (std::find_if(firstCriteriaPersons.begin(), firstCriteriaPersons.end(),
            [person](Person p) {
            return person.getName() == p.getName();
            }) == firstCriteriaPersons.end()) {
                firstCriteriaPersons.push_back(person);
            }
        }

        return firstCriteriaPersons;
    }

    OrCriteria(Criteria& criteria, Criteria& otherCriteria) : m_criteria(criteria),
        m_otherCriteria(otherCriteria) {}

private:
    Criteria& m_criteria;
    Criteria& m_otherCriteria;
};

void printPersons(std::list<Person> persons) {
    for (auto person : persons) {
        std::cout << "Person : [ Name : " << person.getName() << ", Gender : " <<
                  person.getGender() << ", Marital Status : " << person.getMaritalStatus() << " ]" << std::endl;
    }

}

int main() {
    std::list<Person> persons;

    persons.push_back(Person("Robert", "Male", "Single"));
    persons.push_back(Person("John", "Male", "Married"));
    persons.push_back(Person("Laura", "Female", "Married"));
    persons.push_back(Person("Diana", "Female", "Single"));
    persons.push_back(Person("Mike", "Male", "Single"));
    persons.push_back(Person("Bobby", "Male", "Single"));

    printPersons(persons);

    CriteriaMale male = CriteriaMale();
    CriteriaFemale female = CriteriaFemale();
    CriteriaSingle single = CriteriaSingle();
    AndCriteria singleMale = AndCriteria(single, male);
    OrCriteria singleOrFemale = OrCriteria(single, female);

    std::cout << "\nMale:" << std::endl;
    printPersons(male.meetCriteria(persons));

    std::cout << "\nFemale:" << std::endl;
    printPersons(female.meetCriteria(persons));

    std::cout << "\nSingle:" << std::endl;
    printPersons(single.meetCriteria(persons));

    std::cout << "\nSingle Male:" << std::endl;
    printPersons(singleMale.meetCriteria(persons));

    std::cout << "\nSingle Or Female:" << std::endl;
    printPersons(singleOrFemale.meetCriteria(persons));

    return 0;
}