#include "Person.hpp"

Person::Person(int id, string name) : ID_(id), name_(name) {}

Person::Person(int id, string name, string job) : ID_(id), name_(name), job_(job) {}

string Person::getName() { return name_; }

string Person::getJob() { return job_; }