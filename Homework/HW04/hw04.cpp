/*
File: hw04.cpp
Author: Malani Snowden
Purpose: Model a game of medieval times. Create nobles and warriors. Allow for 
         hiring/firing of warriors into/from nobles' armies.
*/

//
// HEADER FILES; NAMESPACE DIRECTIVE
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;


//
// CLASSES: Your Noble and Warrior classes should go here.
//
     /* WARRIOR Class */
class Warrior { // MUST be defined BEFORE Noble class
     friend ostream& operator<<(ostream& os, const Warrior& warrior) {
          os << warrior.name << ": " << warrior.strength;
          return os;
     }

public:
     /* Constructor */
     Warrior(const string& name, int strength) : name(name), strength(strength) {}

     /* Member Functions */
     void die() {
          strength = 0;
     }

     /* Getters and Setters(Modifiers) */
     const string& getName() const { return name; }
     double getStrength() const { return strength; }
     void updateStrength(double strengthRatio) {
          strength -= (strength*strengthRatio);
     }
     bool getEmployment() const { return employmentStatus; }
     void setEmployment(bool newStatus) { 
          employmentStatus = newStatus; 
     }

private:
     /* Member attributes */
     string name;
     double strength;
     bool employmentStatus = false;
};

     /* NOBLE Class */
class Noble {
     friend ostream& operator<<(ostream& os, const Noble& noble) {
          os << noble.name << " has and army of " << noble.army.size();
          for (size_t i = 0; i < noble.army.size(); ++i) {
               os << "\n    " << *(noble.army[i]);
          }
          return os;
     }

public:
     /* Constructor */
     Noble(const string& name) : name(name) {}
     
     /* Member Functions */

     // Find index of warrior within the noble's army
    size_t locateWarrior(const vector<Warrior*>& army, const Warrior& warrior) const {
          for (size_t i = 0; i < army.size(); ++ i) {
          if (army[i] == &warrior) { // if warrior is in army
               return i; // return it's index
          }
          }
          // if warrior not in noble's army
          return army.size(); // return size of army
     }

     // Hire warrior into noble's army
     bool hire(Warrior& warrior) {
          if ((armyStrength == 0 && army.size() != 0) || warrior.getEmployment())
           { // noble is dead or warrior already employed
               cout << name << " failed to hire " << warrior.getName() << endl;
               return false;
          }
          else { // noble alive and warrior unemployed
               Warrior* pWarrior = &warrior;
               army.push_back(pWarrior);
               warrior.setEmployment(true);
               armyStrength += warrior.getStrength();
               return true;
          }
     }

     // Fire warrior from noble's army
     bool fire(Warrior& warrior) {
          size_t index = locateWarrior(army, warrior);

          if ((armyStrength == 0 && army.size() != 0) || index == army.size()) {
               cout << name << " failed to fire " << warrior.getName() << endl;
               return false;
          }
          else {
               for (size_t i = index; i < army.size() - 1; ++i) {
                    army[i+1] = army[i]; // move each warrior infront back one
               }
               // army[army.size() - 1] = nullptr;
               army.pop_back();
               warrior.setEmployment(false);
               armyStrength -= warrior.getStrength();
               cout << warrior.getName() << ", you don't work for me anymore -- "
                    << name << '.' << endl;
               return true;
          }
     }

     // Update strengths of each warrior in noble's army
     void updateStrengths(double strengthRatio) {
          for (size_t i = 0; i < army.size(); ++i) {
               army[i]->updateStrength(strengthRatio);
               armyStrength += army[i]->getStrength();
          }
     }

     // Account for complete death of noble and all warriors in army
     void die() {
          for (size_t i = 0; i < army.size(); ++i) {
               army[i]->die();
          }
          isDead = true;
     }

     void battle(Noble& opponent) {
          cout << name << " battles " << opponent.name << endl;

          if (isDead && opponent.isDead) {
               cout << "Oh, NO! They're both dead! Yuck!" << endl;
          }
          else if (isDead) { // ONLY proponent is dead
               cout << "He's dead, " << opponent.name << endl;
          }
          else if (opponent.isDead) { // ONLY opponent is dead
               cout << "He's dead, " << name << endl;
          }
          else { // Neither warrior is dead
               double strengthRatio;
               if (armyStrength < opponent.armyStrength) { // Opponent stronger
                    strengthRatio = armyStrength/opponent.armyStrength;
                    opponent.updateStrengths(strengthRatio);
                    die();
                    cout << opponent.name << " defeats " << name << endl;
               }
               else if (armyStrength > opponent.armyStrength) { // Opponent weaker
                    strengthRatio = opponent.armyStrength/armyStrength;
                    updateStrengths(strengthRatio);
                    opponent.die();
                    cout << name << " defeats " << opponent.name << endl;
               }
               else { // Warriors have same strength
                    die();
                    opponent.die();
                    cout << "Mutual Annihilation: " << name << " and " 
                         << opponent.name << " die at each other's hands" << endl;
               }
          }
     }

private:
     /* member attributes */
     string name;
     vector<Warrior*> army;
     double armyStrength = 0;
     bool isDead = false;
};


//
// MAIN
///
int main() {
	
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
	
    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";
	
    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
}
