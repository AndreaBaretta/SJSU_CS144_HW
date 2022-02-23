#include <iostream>
using namespace std;
#define MAX_STUDENTS 8
#define MAX_COURSES 128
class Student;
class Course {
   private:
    int id;
    // There are 8 items in the array if MAX_STUDENTS is 8.
    // Initially this array contains nonsense values.
    // The first num_students items in the array contains pointers to actual
    // students who have added the class.
    Student* students[MAX_STUDENTS];
    int num_students;

   public:
    Course();
    Course(int i);
    int GetID();
    void SetID(int i);
    void Print();
    void AddStudent(Student* sptr);
    void PassStudent(int sid);
    Student** StudentsWhoHavePassed(int* len);
};
class Student {
   private:
    int id;
    int classes_passed[MAX_COURSES];
    int num_classes_passed;

   public:
    Student() : id(0), num_classes_passed(0){};
    Student(int i) : id(i), num_classes_passed(0){};
    Student(const Student& s)
        : id(s.id), num_classes_passed(s.num_classes_passed) {
        cout << "CC" << endl;
    };
    void SetID(int i) { id = i; };
    int GetID() { return id; };
    void Print() {
        cout << "student " << id << " has passed " << num_classes_passed
             << " class(es) with these class ids: ";
        for (int i = 0; i < num_classes_passed; i++) {
            cout << classes_passed[i] << " ";
        }
        cout << endl;
    };
    friend class Course;
};
Course::Course() : id(0), num_students(0) {}
Course::Course(int i) : id(i), num_students(0) {}
int Course::GetID() {
    return id;
}
void Course::SetID(int i) {
    id = i;
}
void Course::Print() {
    cout << "Course ID: " << id << " num students: " << num_students << endl;
    cout << " students: ";
    for (int i = 0; i < num_students; i++) {
        cout << students[i]->GetID() << " ";
    }
    cout << endl;
}
void Course::AddStudent(Student* sptr) {
    if (num_students > MAX_STUDENTS)
        return;
    students[num_students] = sptr;
    num_students++;
}
// Write a function PassStudent that takes the ID of a student.
// If there is any Student in this Course with that ID,
// Add this Course's ID to the list of classes passed by the student.
// You may write additional code in the Student class.
void Course::PassStudent(int sid) {}
// Return an array of Student*.
// This array contains pointers to all students who have passed this class.
// Write the length of the array to len.
Student** Course::StudentsWhoHavePassed(int* len) {}
int main() {
    Student students[10];
    for (int i = 0; i < 10; i++) {
        students[i].SetID(100 + i);
    }
    Course courses[6];
    for (int i = 0; i < 6; i++) {
        courses[i].SetID(9000 + i);
    }
    courses[1].AddStudent(&(students[3]));
    courses[1].AddStudent(&(students[6]));
    courses[1].AddStudent(&(students[7]));
    courses[1].AddStudent(&(students[8]));
    courses[1].AddStudent(&(students[9]));
    courses[1].PassStudent(106);
    courses[1].PassStudent(107);
    courses[4].AddStudent(&(students[7]));
    courses[4].PassStudent(107);

    for (int i = 0; i < 10; i++) {
        students[i].Print();
    }

    for (int i = 0; i < 6; i++) {
        courses[i].Print();
    }
    int len = 0;
    Student** passed = courses[1].StudentsWhoHavePassed(&len);
    cout << "passed: ";
    for (int i = 0; i < len; i++) {
        cout << passed[i]->GetID() << " ";
    }
    cout << endl;

    return 0;
}
/*
Sample output:
student 100 has passed 0 class(es) with these class ids:
student 101 has passed 0 class(es) with these class ids:
student 102 has passed 0 class(es) with these class ids:
student 103 has passed 0 class(es) with these class ids:
student 104 has passed 0 class(es) with these class ids:
student 105 has passed 0 class(es) with these class ids:
student 106 has passed 1 class(es) with these class ids: 9001
student 107 has passed 2 class(es) with these class ids: 9001 9004
student 108 has passed 0 class(es) with these class ids:
student 109 has passed 0 class(es) with these class ids:
Course ID: 9000 num students: 0
 students:
Course ID: 9001 num students: 5
 students: 103 106 107 108 109
Course ID: 9002 num students: 0
 students:
Course ID: 9003 num students: 0
 students:
Course ID: 9004 num students: 1
 students: 107
Course ID: 9005 num students: 0
 students:
passed: 106 107
*/