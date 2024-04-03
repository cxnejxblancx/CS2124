/*
Author: Malani Snowden
File: rec08_single.cpp
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student; // forward class declaration

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse(); 

    /* OPTIONAL   */
    void dropStudent(Student*);


private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course*);

    /* OPTIONAL */
    void setName(const string&);
    void removeAllCourses();

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string&);
    // Creates a new student, if none with that name
    bool addStudent(const string&);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Get rid of everything!!!
    void purge();

    /* OPTIONAL METHODS */
    bool changeStudentName(const string&, const string&); 
    bool dropStudentFromCourse(const string&, const string&);
    bool removeStudent(const string&);

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    //


    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}
  
//
// Implementation Code - COURSE
//
ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.name << ": ";
    if (rhs.students.size() != 0) {
        for (size_t i = 0; i < rhs.students.size(); ++i) {
            os << rhs.students[i]->getName() << " ";
        }
    }
    else {
        os << "No Students";
    }
    return os;
}

// Course methods needed by Registrar
Course::Course(const string& name) : name(name) {}
const string& Course::getName() const { return name; }
bool Course::addStudent(Student* student) {
    students.push_back(student);
    return true;
}

// Tell the students that they are no longer in the course
void Course::removeStudentsFromCourse() {
    for (size_t i = 0; i < students.size(); ++i) {
        students[i]->removedFromCourse(this);
    }
    students.clear();
}

/* Optional Implementation */
void Course::dropStudent(Student* student) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (student == students[i]) {
            students[i] = students[i+1];
        }
        // students[students.size() - 1]->removedFromCourse(this);
        students.pop_back();
    }
}


//
// Implementation Code - STUDENT
//
ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if (rhs.courses.size() != 0) {
        for (size_t i = 0; i < rhs.courses.size(); ++i) {
            os << rhs.courses[i]->getName() << " ";
        }
    }
    else {
        os << "No Courses";
    }
    return os;

}

// Student methods needed by Registrar
Student::Student(const string& name) : name(name) {}
const string& Student::getName() const { return name; }
bool Student::addCourse(Course* course) {
    courses.push_back(course);
    return true;
}

// Student method needed by Course::removeStudentsFromCourse
void Student::removedFromCourse(Course* course) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (course == courses[i]) {
            for (size_t j = i; j < courses.size() - 1; ++j) {
                courses[j] = courses[j+1];
            }
            // courses[i] = courses[i+1]; // logic issues
        }
    }
    courses.pop_back();
}

/* Optional Implementation */
void Student::setName(const string& newName) { name = newName; }
void Student::removeAllCourses() {
    for (size_t i = 0; i < courses.size(); ++i) {
        courses[i]->dropStudent(this);
    }
    courses.clear();
}



//
// Implementation Code - REGISTRAR
//
ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report\nCourses:";
    for (size_t i = 0; i < rhs.courses.size(); ++i) {
        os << "\n" << *(rhs.courses[i]);
    }
    os << "\nStudents:";
    for (size_t i = 0; i < rhs.students.size(); ++i) {
        os << "\n" << *(rhs.students[i]);
    }
    os << endl;
    return os;
}

// Registrar private methods
size_t Registrar::findStudent(const string& studentName) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (studentName == students[i]->getName()) {
            return i;
        }
    }
    return students.size();
}
size_t Registrar::findCourse(const string& courseName) const {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courseName == courses[i]->getName()) {
            return i;
        }
    }
    return courses.size();
}

Registrar::Registrar() {}

// Creates a new course, if none with that name
bool Registrar::addCourse(const string& courseName) {
    size_t courseIndex = findCourse(courseName);
    if (courseIndex == courses.size()){
        Course* newCourse = new Course(courseName);
        courses.push_back(newCourse);
        return true;
    }
    return false;
}
// Creates a new student, if none with that name
bool Registrar::addStudent(const string& studentName) {
    size_t studentIndex = findStudent(studentName);
    if (studentIndex == students.size()){
        Student* newStudent = new Student(studentName);
        students.push_back(newStudent);
        return true;
    }
    return false;
}

// If the student and the course exist, then enroll the student.
bool Registrar::enrollStudentInCourse(const string& studentName,
                            const string& courseName) {
    size_t studentIndex = findStudent(studentName);
    size_t courseIndex = findCourse(courseName);
    if ((studentIndex != students.size()) && (courseIndex != courses.size())) {
        students[studentIndex]->addCourse(courses[courseIndex]);
        courses[courseIndex]->addStudent(students[studentIndex]);
        return true;
    }
    return false;
}

// Unenroll the students from the course and remove the course
// from the Registrar.
bool Registrar::cancelCourse(const string& courseName) {
    size_t courseIndex = findCourse(courseName);
    if (courseIndex != courses.size()) {
        Course* target = courses[courseIndex];
        courses[courseIndex]->removeStudentsFromCourse();
        delete target;
        for (size_t i = courseIndex; i < courses.size() - 1; ++i) {
            courses[i] = courses[i + 1];
        }
        // delete courses[courses.size() - 1]; // wrong course
        courses.pop_back();
        return true;
    }
    return false;
}

// Get rid of everything!!!
void Registrar::purge() {
    for (size_t i = 0; i < courses.size(); ++i) {
        cancelCourse(courses[i]->getName());
    }
    for (size_t i = 0; i < students.size(); ++i) {
        delete students[i];
    }
    courses.clear();
    students.clear();
}

/* OPTIONAL METHODS */
bool Registrar::changeStudentName(const string& oldName, const string& newName) {
    size_t studentIndex = findStudent(oldName);
    if (studentIndex != students.size()) {
        students[studentIndex]->setName(newName);
        return true;
    }
    return false;
}

bool Registrar::dropStudentFromCourse(const string& studentName, const string& courseName) {
    size_t studentIndex = findStudent(studentName);
    size_t courseIndex = findCourse(courseName);
    if ((studentIndex != students.size()) && (courseIndex != courses.size())) {
        courses[courseIndex]->dropStudent(students[studentIndex]);
        students[studentIndex]->removedFromCourse(courses[courseIndex]);
        return true;
    }
    return false;
}
    
bool Registrar::removeStudent(const string& name) {
    size_t studentIndex = findStudent(name);
    if (studentIndex != students.size()) {
        Student* target = students[studentIndex];
        students[studentIndex]->removeAllCourses();
        delete target;
        for (size_t i = studentIndex; i < students.size() - 1; ++i) {
            students[i] = students[i + 1];
        }
        // delete students[students.size() - 1]; // 
        students.pop_back();
        return true;
    }
    return false;

}
