#ifndef STUDENT_MANAGEMENT_SYSTEM_H
#define STUDENT_MANAGEMENT_SYSTEM_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// Abstract Class
class Person {
public:
    virtual void displayDetails() = 0;
    virtual ~Person() {}
};

// Base Class
class Student : public Person {
protected:
    int studentID;
    string name;
    int age;

public:
    Student(int id, string student_name, int student_age);

    int getStudentID() const;
    string getName() const;
    int getAge() const;

    void setName(string student_name);
    void setAge(int student_age);

    virtual void displayDetails() override;
    virtual ~Student();
};

// Derived Class 1
class UndergraduateStudent : public Student {
private:
    string major;

public:
    UndergraduateStudent(int id, string student_name, int student_age, string student_major);

    void displayDetails() override;
    ~UndergraduateStudent();
};

// Derived Class 2
class GraduateStudent : public Student {
private:
    string thesisTitle;

public:
    GraduateStudent(int id, string student_name, int student_age, string thesis);

    void displayDetails() override;
    ~GraduateStudent();
};

// File Handling Class
class FileManager {
public:
    static void saveToFile(const string &filename, const vector<Student *> &students);
    static void readFromFile(const string &filename);
};

#endif
