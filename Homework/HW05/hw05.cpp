/*
File: hw05.cpp
Author: Malani Snowden
Purpose: Model a game of medieval times. Create nobles and warriors on the HEAP.
         Allow for hiring/firing of warriors into/from nobles' armies.
*/

//
// HEADER FILES; NAMESPACE DIRECTIVE
//
#include <iostream>
#include <fstream>
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
        if (isDead || warrior.getEmployment())
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

        if ( isDead || index == army.size() ) {
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

    /* Getters and Setters(Modifiers) */
    const string& getName() const { return name; }

private:
    /* member attributes */
    string name;
    vector<Warrior*> army;
    double armyStrength = 0;
    bool isDead = false;
};

//
// FUNCTION PROTOTYPES
//
void readFile(ifstream& file);
size_t locateNoble(const vector<Noble*>& nobles, const string& name);
size_t locateWarrior(const vector<Warrior*>& warriors, const string& name);
void createNoble(vector<Noble*>& nobles, const string& name);
void createWarrior(vector<Warrior*>& warriors, const string& name,
     int strength);
void battle(const string& nobleName1, const string& nobleName2);
void displayStatus(const vector<Noble*>& nobleName1, 
     const vector<Warrior*>& nobleName2);


//
// MAIN
///
int main() {

    ifstream file("nobleWarriors.txt");
    if (!file) { 
        cerr << "ERROR: Failed to open 'nobleWarrior.txt'" << endl;
        exit(1);
    }

    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    string command;
    while (file >> command) {
        string nobleName;
        string warriorName;
        if (command == "Noble") {
            file >> nobleName;
            createNoble(nobles, nobleName);
        }
        else if (command == "Warrior") {
            int strength;
            file >> warriorName >> strength;
            createWarrior(warriors, warriorName, strength);
        }
        else if (command == "Hire") {
            file >> nobleName >> warriorName;
            size_t nobleIndex = locateNoble(nobles, nobleName);
            size_t warriorIndex = locateWarrior(warriors, warriorName);
            if ((nobleIndex != nobles.size()) && 
                (warriorIndex != warriors.size())) {
                Noble noble = *(nobles[nobleIndex]);
                Warrior warrior = *(warriors[warriorIndex]);
                noble.hire(warrior);
            }
            else {
                cout << "ERROR: Noble and/or warrior does not exist!" << endl;
            }
        }
        else if (command == "Fire") {
            file >> nobleName >> warriorName;
            size_t nobleIndex = locateNoble(nobles, nobleName);
            size_t warriorIndex = locateWarrior(warriors, warriorName);
            if ((nobleIndex != nobles.size()) && 
                (warriorIndex != warriors.size())) {
                nobles[nobleIndex]->fire(*warriors[warriorIndex]);
            }
            else {
                cout << "ERROR: Noble and/or warrior does not exist!" << endl;
            }
        }
        else if (command == "Battle") {
            string name1, name2;
            file >> name1 >> name2;
            size_t nobleIndex1 = locateNoble(nobles, name1);
            size_t nobleIndex2 = locateNoble(nobles, name2);
            if ((nobleIndex1 != nobles.size()) && (nobleIndex2 != nobles.size())) {
                nobles[nobleIndex1]->battle(*nobles[nobleIndex2]);
            }
            else {
                cout << "ERROR: One or both nobles do not exist!" << endl;
            }
        }
        else if (command == "Status") {
            displayStatus(nobles, warriors);
        }
        else {
            for (size_t i = 0; i < warriors.size(); ++i) {
                delete warriors[i];
                warriors[i] = nullptr;
            }
            warriors.clear();

            for (size_t i = 0; i < nobles.size(); ++i) {
                delete nobles[i];
                nobles[i] = nullptr;
            }
            nobles.clear();
        }
    }
}

//
// FUNCTION DEFININTIONS
//
size_t locateNoble(const vector<Noble*>& nobles, const string& name) {
    for (size_t i = 0; i < nobles.size(); ++i) {
        if (nobles[i]->getName() == name) { return i; }
    }
    return nobles.size();
}

size_t locateWarrior(const vector<Warrior*>& warriors, const string& name) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i]->getName() == name) { return i; }
    }
    return warriors.size();
}

void createNoble(vector<Noble*>& nobles, const string& name) {
    if (locateNoble(nobles, name) == nobles.size()) {
        Noble* newNoble = new Noble(name);
        nobles.push_back(newNoble);
    }
    else {
        cout << "ERROR: Noble with that name already exists!" << endl;
    }
}

void createWarrior(vector<Warrior*>& warriors, const string& name, int strength) {
    if (locateWarrior(warriors, name) == warriors.size()) {
        Warrior* newWarrior = new Warrior(name, strength);
        warriors.push_back(newWarrior);
    }
    else {
        cout << "ERROR: Warrior with that name already exists!" << endl;
    }
}

void displayStatus(const vector<Noble*>& nobles, const vector<Warrior*>& warriors) {
    cout << "Status\n======\nNobles:" << endl;
    for (size_t i = 0; i < nobles.size(); ++i) {
        cout << *nobles[i] << endl;
    }

    cout << "Unemployment Warriors:" << endl;
    int numUnemployed = 0;
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (!warriors[i]->getEmployment()) {
            numUnemployed += 1;
            cout << *warriors[i] << endl; 
        }
    }
    if (numUnemployed == 0) {
        cout << "NONE" << endl;
    }
}
