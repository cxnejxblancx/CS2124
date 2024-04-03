/* 
Malani Snowden
course.cpp
*/

#include "Course.h"
#include "Student.h"
#include <iostream> // optional
#include <vector> // optional
#include <string> // optional
using namespace std;

namespace BrooklynPoly{
    //
    // Implementation Code - COURSE
    //

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

}