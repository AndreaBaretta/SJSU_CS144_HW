// Note: You are not allowed to add or change member variables of any class.
// Read all the code and comments first, then answer all questions.

#include <iostream>

using namespace std;

#define MAX_STUDENTS 8
#define MAX_COURSES 6

class Student;

class Course {
   private:
    int id;
    int num_units;
    // There are 8 items in the array if MAX_STUDENTS is 8.
    // Initially this array contains nonsense values.
    // The first num_students items in the array contains pointers to actual
    // students who have added the class.
    Student* students[MAX_STUDENTS];
    int num_students;

   public:
    Course(int i, int u);
    int GetID();
    void Print();
    void AddStudent(Student* sptr);
    void CompleteStudent(int id, float grade);
    int GetNumUnits() { return num_units; }
};

class Student {
   private:
    int id;
    int num_courses;
    // There are 6 items in the array if MAX_COURSES is 6.
    // Initially this array contains nonsense values.
    // The first num_courses items in the array contains pointers to actual
    // courses added by the student.
    Course* courses[MAX_COURSES];
    float gpa;
    int units_completed;

   public:
    Student(int i) : id(i), num_courses(0), gpa(0.0), units_completed(0.0){};
    int GetID() { return id; };

    // Q1a. [3 points] Write the AddCourse function.
    // If number of courses has reached maximum, return false.
    // Otherwise,
    // update member variables "courses" and "num_courses" appropriately,
    // and return true.
    // This function is only called by Course::AddStudent.
    bool AddCourse(Course* cptr) {
        if (num_courses == MAX_COURSES) {
            return false;
        } else {
            courses[num_courses] = cptr;
            ++num_courses;
            return true;
        }
    };

    // Q1b. [3 points] Write the RemoveCourse function.
    // Look for the input Course in the courses array.
    // If found, remove the course by updating member variables
    // "courses" and "num_courses" appropriately.
    // This function is only called by Course::CompleteStudent.
    void RemoveCourse(Course* cptr) {
        std::size_t index = 0;
        bool found = false;
        for (std::size_t i = 0; i < num_courses; ++i) {
            if (courses[i] == cptr) {
                index = i;
                found = true;
                break;
            }
        }
        if (!found) {
            return;
        } else {
            for (std::size_t i = index; i < num_courses - 1; ++i) {
                courses[i] = courses[i + 1];
            }
            if (index == num_courses - 1) {
                courses[index] = nullptr;
            }
            --num_courses;
        }
    };

    void Print() {
        cout << "student " << id << " is taking " << num_courses
             << " class(es) with these class ids: ";
        for (int i = 0; i < num_courses; i++) {
            cout << courses[i]->GetID() << " ";
        }
        cout << " gpa: " << gpa << " units completed: " << units_completed
             << endl;
    };

    float GetGPA() { return gpa; }

    void SetGPA(float gpa) { this->gpa = gpa; }

    int GetUnitsCompleted() { return units_completed; }

    void AddUnits(int units) { units_completed += units; }

    int GetCurrentUnits() {
        int total_units = 0;
        for (std::size_t i = 0; i < num_courses; ++i) {
            total_units += courses[i]->GetNumUnits();
        }
        return total_units;
    }
};

Course::Course(int i, int u) : id(i), num_students(0), num_units(u) {}

int Course::GetID() {
    return id;
}

void Course::Print() {
    cout << "Course ID: " << id << " num students: " << num_students << endl;
    cout << " students: ";
    for (int i = 0; i < num_students; i++) {
        cout << students[i]->GetID() << " ";
    }
    cout << endl;
}

// Q2. [3 points] Write the AddStudent function.
// If there is still room in this Course
// (if num_students is less than MAX_STUDENTS), add the student to the Course
// by updating private members "students" and "num_students" appropriately.
// Call the "AddCourse" function in Student class.
// Do not add Student to the Course if the "AddCourse" function in Student
// returns false.
void Course::AddStudent(Student* sptr) {
    if (num_students < MAX_STUDENTS) {
        if (sptr->AddCourse(this)) {
            students[num_students] = sptr;
            ++num_students;
        }
    }
}

// Q3. [6 points] Write the CompleteStudent function.
// Search for the student with the given id.
// The grade point the student received for this class is given in
// the "grade" parameter.
// Recalculate and update the student's gpa
// according to the usual manner of calculating gpa.
// GPA = (Sum_over_all_classes ( GP_n * Units_n )) / total_units
//   where GP_n is the grade point of the nth class,
//   and Units_n is the number of units of the nth class.
// Also update the student's number of units completed.
// Also remove Course from Student's "courses" member variable.
// You may write additional code in the Student class to make this work;
// however, you may not make private members of Student become public.
// Remove this student from students member variable
// and update num_students appropriately.
void Course::CompleteStudent(int id, float grade) {
    Student* sptr = nullptr;
    std::size_t student_index = 0;
    for (std::size_t i = 0; i < num_students; ++i) {
        if (students[i]->GetID() == id) {
            sptr = students[i];
            student_index = i;
            break;
        }
    }
    if (sptr == nullptr) {
        return;
    }
    float total_grade_point = sptr->GetGPA() * sptr->GetUnitsCompleted();
    total_grade_point += grade * num_units;
    sptr->AddUnits(num_units);
    sptr->SetGPA(total_grade_point / sptr->GetUnitsCompleted());
    sptr->RemoveCourse(this);
    for (std::size_t i = student_index; i < num_students - 1; ++i) {
        students[i] = students[i + 1];
    }
    if (student_index == num_students - 1) {
        students[student_index] = nullptr;
    }
    --num_students;
}

class University {
   private:
    Student** all_students;
    Course** all_courses;
    int all_students_capacity;
    int all_courses_capacity;
    int num_students;
    int num_courses;

   public:
    University()
        : num_students(0),
          num_courses(0),
          all_students(nullptr),
          all_courses(nullptr),
          all_students_capacity(0),
          all_courses_capacity(0){};

    // Q4: [3 points]
    // Write the destructor to free all dynamically allocated memory.
    ~University() {
        for (std::size_t i = 0; i < all_students_capacity; ++i) {
            delete all_students[i];
        }
        for (std::size_t i = 0; i < all_courses_capacity; ++i) {
            delete all_courses[i];
        }
        delete[] all_students;
        delete[] all_courses;
    };

    // Q5a: [3 points]
    // Write AddStudent to make a new Student object with the given id
    // and add it to the all_students array.
    // Dynamically allocate memory if necessary.
    // Update num_students member variable appropriately.
    // Make sure you free memory as appropriate to prevent memory leak.
    void AddStudent(int id) {
        if (all_students_capacity == 0) {
            Student** new_all_students = new Student*[1];
            delete[] all_students;
            all_students = new_all_students;
            all_students_capacity = 1;
        } else if (num_students == all_students_capacity) {  // Make some room
            Student** new_all_students =
                new Student*[2 * all_students_capacity];
            for (std::size_t i = 0; i < num_students; ++i) {
                new_all_students[i] = all_students[i];
            }
            delete[] all_students;
            all_students = new_all_students;
            all_students_capacity *= 2;
        }

        all_students[num_students] = new Student(id);
        ++num_students;
    };

    // Q5b: [3 points]
    // Write AddCourse to make a new Course object with the given id
    // and add it to the all_courses array.
    // Dynamically allocate memory if necessary.
    // Update num_courses member variable appropriately.
    // Make sure you free memory as appropriate to prevent memory leak.
    void AddCourse(int id, int num_units) {
        if (all_courses_capacity == 0) {
            Course** new_all_courses = new Course*[1];
            delete[] all_courses;
            all_courses = new_all_courses;
            all_courses_capacity = 1;
        } else if (num_courses == all_courses_capacity) {  // Make some room
            Course** new_all_courses = new Course*[2 * all_courses_capacity];
            for (std::size_t i = 0; i < num_courses; ++i) {
                new_all_courses[i] = all_courses[i];
            }
            delete[] all_courses;
            all_courses = new_all_courses;
            all_courses_capacity *= 2;
        }

        all_courses[num_courses] = new Course(id, num_units);
        ++num_courses;
    };

    // Q6a: [3 points] Write GetTopStudent.
    // Return a pointer to the student in the University with the highest GPA.
    // You may write additional code in Student class but you may not
    // change private member variables into public member variables.
    // If there are more than one Student having the highest GPA,
    // return any one of them.
    Student* GetTopStudent() {
        if (num_students == 0) {
            return nullptr;
        }
        Student* best_student = all_students[0];
        for (std::size_t i = 0; i < num_students; ++i) {
            if (all_students[i]->GetGPA() > best_student->GetGPA()) {
                best_student = all_students[i];
            }
        }
        return best_student;
    };

    // Q6b: [3 points] Write GetStudentTakingMostUnits.
    // Return a pointer to the student in the University currently taking
    // the most number of units (not the number of units completed).
    // You may write additional code in Student and Course classes but you
    // may not change private member variables into public member variables.
    // If there are more than one Student taking the most number of units,
    // return any one of them.
    Student* GetStudentTakingMostUnits() {
        if (num_students == 0) {
            return nullptr;
        }
        Student* best_student = all_students[0];
        for (std::size_t i = 0; i < num_students; ++i) {
            if (all_students[i]->GetCurrentUnits() >
                best_student->GetCurrentUnits()) {
                best_student = all_students[i];
            }
        }
        return best_student;
    };

    void Simulate() {
        for (int i = 0; i < 16; i++) {
            AddStudent(i);
        }
        for (int i = 0; i < 8; i++) {
            AddCourse(1000 + i, 3);
        }
        all_courses[3]->AddStudent(all_students[1]);
        all_courses[3]->AddStudent(all_students[2]);
        all_courses[3]->AddStudent(all_students[3]);
        all_courses[2]->AddStudent(all_students[1]);
        all_courses[2]->AddStudent(all_students[2]);
        all_courses[1]->AddStudent(all_students[1]);
        all_courses[1]->AddStudent(all_students[2]);
        all_courses[1]->AddStudent(all_students[3]);
        all_courses[1]->AddStudent(all_students[4]);
        all_courses[3]->CompleteStudent(2, 3.4);
        Student* sptr = GetTopStudent();
        if (sptr != nullptr) {
            cout << "Top student:" << endl;
            sptr->Print();
        }

        sptr = GetStudentTakingMostUnits();
        if (sptr != nullptr) {
            cout << "Most units:" << endl;
            sptr->Print();
        }
    };
};

int main() {
    University U1;
    U1.Simulate();
    return 0;
}
