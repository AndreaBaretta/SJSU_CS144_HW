#include <iostream>
#include <unordered_map>

using namespace std;

class Person {
   private:
    int ssn;

   public:
    string name;
    Person(string n, int s) : name(n), ssn(s){};
    Person() : name("unknown"), ssn(0){};
};

class Faculty : public virtual Person {
    int fac_id;

   public:
    Faculty(string n, int i, int j) : Person(n, i), fac_id(j){};
    string GetName() { return name; };
    void SetName(const string& n) { name = n; };
};

class Student : public virtual Person {
    int stu_id;
    float gpa;

   public:
    Student() : stu_id(0), gpa(0.0){};
    Student(string n, int i, int j) : Person(n, i), stu_id(j), gpa(0.0){};
    string FindName() { return name; };
    void ChangeName(const string& n) { name = n; };
    void SetGPA(float g) { gpa = g; };
    float GetGPA() { return gpa; };
    int GetStudentID() { return stu_id; };
};

class TA : public Faculty, public Student {
   public:
    TA(string n, int fid, int sid, int ssn)
        : Faculty(n, ssn, fid), Student(n, ssn, sid){};
};

class University {
   private:
    unordered_map<int, Student> students;

   public:
    University(){};
    void AddStudent(Student s) { students[s.GetStudentID()] = s; }
    Student& GetStudent(int id) { return students[id]; }
};

int main() {
    // [6 points]
    // Q4. Change the definition of the classes above so that the code below
    // prints "Name is: Betty".
    // In other words, there is only one copy of "name" in ta1,
    // so that ChangeName() and GetName() both refer to the same variable.
    TA ta1("Ann", 200, 300, 400);
    ta1.Student::ChangeName("Betty");
    cout << "Name is: " << ta1.Faculty::GetName() << endl;

    // [6 points]
    // Q5. Write the University class above.
    // This class supports two functions: AddStudent and GetStudent.
    // AddStudent() receives a Student as argument and stores it
    // in a data structure.
    // Note that every Student has a unique stu_id.
    // GetStudent() receives an integer n as argument and returns a reference
    // to the Student with the stu_id n.
    // Use an efficient data structure to allow quick lookup of stu_id.
    // Goal is constant time insertion of a Student (AddStudent),
    // and constant time lookup of a Student (GetStudent).
    University U1;
    U1.AddStudent(Student("Cameron", 2, 3));
    for (int i = 5; i < 10000; i++) {
        U1.AddStudent(Student("Studious Bob " + to_string(i), i, i + 1));
    }
    Student& S1 = U1.GetStudent(2);
    S1.SetGPA(3.7);
    Student& S2 = U1.GetStudent(2);
    cout << "GPA: " << S2.GetGPA() << endl;
    cout << "Student 2993 name is: " << U1.GetStudent(2993).FindName() << endl;

    return 0;
}
