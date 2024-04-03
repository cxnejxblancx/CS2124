/* 
Malani Snowden
student.cpp
*/

#include "Student.h"
#include "Course.h"
#include <iostream> // optional
#include <vector> // optional
#include <string> // optional
using namespace std;

namespace BrooklynPoly{
    //
    // Implementation Code - STUDENT
    //

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
}