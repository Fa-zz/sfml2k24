#include <string>
#include <iostream>
using namespace std;

class Person {
public:
    Person(int id, string name);
    Person(int id, string name, string occupation);

    void print() const {
        std::cout << "ID: " << ID << ", Name: " << name << ", Occupation: " << occupation << std::endl;
    }
private:
    int ID;
    string name;
    string occupation;
    int gender;
};
