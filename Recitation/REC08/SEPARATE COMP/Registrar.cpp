/* 
Malani Snowden
registrar.cpp
*/

#include "Registrar.h"
#include "Course.h"
#include "Student.h"
#include <iostream> // optional
#include <vector> // optional
#include <string> // optional
using namespace std;

namespace BrooklynPoly{
    //
    // Implementation Code - REGISTRAR
    //

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
}