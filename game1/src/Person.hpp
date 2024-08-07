#pragma once
#include <string>
#include <iostream>
using namespace std;

class Person {
public:
    Person(int id, string name);
    Person(int id, string name, string job);
    string getName();
    string getJob();

    void print() const {
        std::cout << "ID: " << ID_ << ", Name: " << name_ << ", Job: " << job_ << std::endl;
    }
private:
    int ID_;
    string name_;
    string job_;
    int gender_;
};
