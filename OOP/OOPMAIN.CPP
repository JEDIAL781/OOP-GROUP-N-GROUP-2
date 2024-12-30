#include <iostream>//so as to allow input of user data
#include <fstream>//so as to write and read from files
#include <string>
#include <vector> //so as to use  the vector conatainer
#include <stdexcept> //so as to use exceptions
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
    // Constructor
    Student(int id, string student_name, int student_age) : studentID(id), name(student_name), age(student_age) {}

    // Getter and Setter methods (Encapsulation)
    int getStudentID() const { return studentID; }
    string getName() const { return name; }
    int getAge() const { return age; }

    void setName(string student_name) { name = student_name; }
    void setAge(int student_age) { 
        if (student_age < 0) {
            throw invalid_argument("Age cannot be negative!");
        }
        age = student_age; 
    }

    // Virtual function for polymorphism
    virtual void displayDetails() override {
        cout << "Student ID: " << studentID << ", Name: " << name << ", Age: " << age << endl;
    }

    // Destructor
    virtual ~Student() {
        cout << "Destructor called for Student: " << name << endl;
    }
};

// Derived Class 1
class UndergraduateStudent : public Student {
  private:
    string major;

  public:
    UndergraduateStudent(int id, string student_name, int student_age, string student_major)
        : Student(id, student_name, student_age), major(student_major) {}

    // Method Overriding
    void displayDetails() override {
        cout << "Undergraduate Student\n";
        Student::displayDetails();
        cout << "Major: " << major << endl;
    }

    ~UndergraduateStudent() {
        cout << "Destructor called for Undergraduate Student: " << name << endl;
    }
};

// Derived Class 2
class GraduateStudent : public Student {
  private:
    string thesisTitle;

  public:
    GraduateStudent(int id, string student_name, int student_age, string thesis)
        : Student(id, student_name, student_age), thesisTitle(thesis) {}

    // Method Overriding (Polymorphism)
    void displayDetails() override {
        cout << "Graduate Student\n";
        Student::displayDetails();
        cout << "Thesis Title: " << thesisTitle << endl;
    }

    ~GraduateStudent() {
        cout << "Destructor called for Graduate Student: " << name << endl;
    }
};

// File Handling Class
class FileManager {
  public:
    static void saveToFile(const string &filename, const vector<Student *> &students) {
        ofstream file(filename, ios::out);
        if (!file) {
            throw runtime_error("Unable to open file for writing.");
        }
        for (const auto &student : students) {
            file << student->getStudentID() << "," << student->getName() << "," << student->getAge() << endl;
        }
        file.close();
    }

    static void readFromFile(const string &filename) {
        ifstream file(filename, ios::in);
        if (!file) {
            throw runtime_error("Unable to open file for reading.");
        }
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
};

int main() {
    vector<Student *> students;
    string filename = "students.txt";

    try {
        int choice;
        do {
            cout << "Student Management System\n";
            cout << "1. Add Undergraduate Student\n";
            cout << "2. Add Graduate Student\n";
            cout << "3. Display All Students\n";
            cout << "4. Save Students to File\n";
            cout << "5. Read Students from File\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int id, age;
                    string name, major;
                    cout << "Enter Student ID: ";
                    cin >> id;
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Age: ";
                    cin >> age;
                    cout << "Enter Major: ";
                    cin.ignore();
                    getline(cin, major);
                    students.push_back(new UndergraduateStudent(id, name, age, major));
                    cout << "Undergraduate student added successfully.\n";
                    break;
                }
                case 2: {
                    int id, age;
                    string name, thesis;
                    cout << "Enter Student ID: ";
                    cin >> id;
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Age: ";
                    cin >> age;
                    cout << "Enter Thesis Title: ";
                    cin.ignore();
                    getline(cin, thesis);
                    students.push_back(new GraduateStudent(id, name, age, thesis));
                    cout << "Graduate student added successfully.\n";
                    break;
                }
                case 3: {
                    cout << "Displaying All Students:\n";
                    for (auto &student : students) {
                        student->displayDetails();
                        cout << "------------------" << endl;
                    }
                    break;
                }
                case 4: {
                    FileManager::saveToFile(filename, students);
                    cout << "Students saved to file: " << filename << endl;
                    break;
                }
                case 5: {
                    cout << "Reading students from file:\n";
                    FileManager::readFromFile(filename);
                    break;
                }
                case 6: {
                    cout << "Exiting the program.\n";
                    break;
                }
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);

    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }


    for (auto &student : students) {
        delete student;
    }

    return 0;
}
