/* 
Malani Snowden
registrar.h
*/

#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <iostream>
#include <vector>
#include <string>

namespace BrooklynPoly{
    class Course; // forward class declaration
    class Student; // forward class declaration

    class Registrar {
        friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
    public:
        Registrar();

        // Creates a new course, if none with that name
        bool addCourse(const std::string&);
        // Creates a new student, if none with that name
        bool addStudent(const std::string&);

        // If the student and the course exist, then enroll the student.
        bool enrollStudentInCourse(const std::string& studentName,
                                const std::string& courseName);

        // Unenroll the students from the course and remove the course
        // from the Registrar.
        bool cancelCourse(const std::string& courseName);

        // Get rid of everything!!!
        void purge();

        /* OPTIONAL METHODS */
        bool changeStudentName(const std::string&, const std::string&); 
        bool dropStudentFromCourse(const std::string&, const std::string&);
        bool removeStudent(const std::string&);

    private:
        size_t findStudent(const std::string&) const;
        size_t findCourse(const std::string&) const;

        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}

#endif