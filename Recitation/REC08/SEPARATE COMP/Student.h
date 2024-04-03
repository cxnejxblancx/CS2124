/* 
Malani Snowden
student.h
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>

namespace BrooklynPoly{
    class Course; // forward class declaration

    class Student {
        friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
    public:
        // Student methods needed by Registrar
        Student(const std::string& name);
        const std::string& getName() const;
        bool addCourse(Course*);

        // Student method needed by Course::removeStudentsFromCourse
        void removedFromCourse(Course*);

        /* OPTIONAL */
        void setName(const std::string&);
        void removeAllCourses();

    private:
        std::string name;
        std::vector<Course*> courses;
    }; 
}

#endif