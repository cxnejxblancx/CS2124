/*
  rec05.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


//
// CLASSES
//

/* SECTION Class */
class Section {
     //
     // Nested Classes
     //

     /* STUDENT Class */
     class StudentRecord {
          friend ostream& operator<<(ostream& os, const StudentRecord& record) {
               os << "Name: " << record.studentName << ", Grades:";
               for (size_t i = 0; i < record.grades.size(); ++i) {
                    os << ' ' << record.grades[i];
               }
               return os;
          }
     public:
          /* Constructor */
          StudentRecord(const string& studentName) : studentName(studentName), grades(14, -1) {}

          /* Getters and Setters (Modifiers)*/
          const string& getStudentName() const { return studentName; }          
          void updateGrade(int grade, size_t index) {
               grades[index] = grade;
          }

     private:
          string studentName;
          vector<int> grades;
     };

     /* TIMESLOT Class */
     class TimeSlot {
          friend ostream& operator<<(ostream& os, const TimeSlot& timeSlot) {
               os << "Time slot: [Day: " << timeSlot.weekday << ", Start time: ";
               if (timeSlot.time < 12) {
                    os << timeSlot.time << "am]";
               }
               else if (timeSlot.time == 12) {
                    os << timeSlot.time << "pm]";
               }
               else {
                    os << timeSlot.time - 12 << "pm]";
               }
               return os;
          }

     public:
          /* Constructor */
          TimeSlot(const string& weekday, unsigned time) : weekday(weekday), time(time) {}

     private:
          string weekday;
          unsigned time;
     };

     /* Output Operator */
     friend ostream& operator<<(ostream& os, const Section& section) {
          os << "Section: " << section.name << ", " << section.timeSlot << ", ";
          if (section.records.size() == 0) {
               os << "Students: None" << endl;
          }
          else {
               os << "Students: " << endl;
               for (size_t i = 0; i < section.records.size(); ++i) {
                    os << *(section.records[i]) << endl;
               }
          }
          return os;
     }

public:
     /* Constructor */
     Section(const string& name, const string& weekday, unsigned time) : name(name), timeSlot(weekday, time) {}


     /* COPY CONTROL */
     ~Section() {
          cout << "Section " << name << " is being deleted" << endl;
          reset();
     } // DESTRUCTOR

     Section(const Section& section) : name(section.name), timeSlot(section.timeSlot) {
          for (size_t i = 0; i < section.records.size(); ++i) {
               StudentRecord* newStudent = new StudentRecord(*section.records[i]); // REVIEW THIS !!!
               records.push_back(newStudent);
          }  
     } // COPY CONSTRUCTOR

     // Section& operator=(const Section& section) {
     //      if (this != &section) {

     //         return
     //      }
     // } // ASSIGNMENT OPERATOR

     /* Member Functions */
     void addStudent(const string& name) {
          records.push_back(new StudentRecord(name)); // for things on the heaper use PUSH_BACK to account for copying !!!!
     }

     size_t locateStudent(const string& name) const {
          for (size_t i = 0; i < records.size(); ++i) {
               if (name == records[i]->getStudentName()) {
                    return i;
               }
          }
          return records.size();
     }

     void reset() {
          for (size_t i = 0; i < records.size(); ++i) {
               cout << "Deleting " << records[i]->getStudentName() << endl;
               delete records[i];
               records[i] = nullptr;
          }
          records.clear();
     }

     /* Getters and Setters (Modifiers)*/
     bool updateRecord(int grade, size_t index, size_t week) {
          if (index != records.size()) {
               records[index]->updateGrade(grade, week-1);
               return true;
          }
          return false;
     }

private:
     string name;
     TimeSlot timeSlot;
     vector<StudentRecord*> records;
};


/* LABWORKER Class */
class LabWorker {
     friend ostream& operator<<(ostream& os, const LabWorker& labWorker) {
          os << labWorker.name;
          if (labWorker.section == nullptr) {
               os << " does not have a section" << endl;
          }
          else {
               os << " has " << *(labWorker.section) << endl;
          }
          return os;
     }

public:
     /* Constructor */
     LabWorker(const string& name) : name(name) {}

     /* Member Functions */
     bool addSection(Section& assignedSection) { 
          section = &assignedSection;
          if (section) {
               return true;
          }
          return false;
          
     }

     bool addGrade(const string& studentName, int grade, size_t week) { 
          size_t studentLocation = section->locateStudent(studentName);
          return section->updateRecord(grade, studentLocation, week);
     }

private:
     string name;
     Section* section = nullptr;
};


// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
