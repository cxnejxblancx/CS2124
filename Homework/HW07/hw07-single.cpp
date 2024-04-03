/*
File: hw07-single.cpp
Author: Malani Snowden
Purpose: Model a game of medieval times. Allow for hiring, firing, and running
         away of warriors.
*/

// Comment out these two includes for the single file solution
//#include "Noble.h"
//#include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Comment out this "using namespace" for the single file solution
//using namespace WarriorCraft;

//
// CLASSES
//

/* Forward class declaration */
class Noble;

/* WARRIOR Class */
class Warrior { 
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
    /* Constructor */
    Warrior(const string& name, int strength);

    /* Member Functions */
    void die();

    /* Getters and Setters(Modifiers) */
    const string& getName() const;
    double getStrength() const;
    void updateStrength(double strengthRatio);
    Noble* getEmployer() const;
    void setEmployer(Noble* newEmployer);
    bool isHired() const;
    void runaway();

private:
    /* Member attributes */
    string name;
    double strength;
    Noble* employer;
};


/* NOBLE Class */
class Noble {
    friend ostream& operator<<(ostream& os, const Noble& noble);

public:
    /* Constructor */
    Noble(const string& name);
        
    /* Member Functions */

    // Find index of warrior within the noble's army
    size_t locateWarrior(const vector<Warrior*>& army, const Warrior& warrior) const;

    // Hire warrior into noble's army
    bool hire(Warrior& warrior);

    // Fire warrior from noble's army
    bool fire(Warrior& warrior);

    // Accout for warrior running away
    void lostWarrior(Warrior* warrior);

    // Update strengths of each warrior in noble's army
    void updateStrengths(double strengthRatio);

    // Account for complete death of noble and all warriors in army
    void die();

    void battle(Noble& opponent);

    /* Getters and Setters(Modifiers) */
    const string& getName() const;

private:
    /* member attributes */
    string name;
    vector<Warrior*> army;
    double armyStrength;
    bool isDead;
};



int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha 
	 << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha 
	 << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

//
// Warrior Implementation Code
//
ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength;
        return os;
    }
/* Constructor */
Warrior::Warrior(const string& name, int strength) : name(name), strength(strength) {}

/* Member Functions */
void Warrior::die() { strength = 0; }

/* Getters and Setters(Modifiers) */
const string& Warrior::getName() const { return name; }
double Warrior::getStrength() const { return strength; }
void Warrior::updateStrength(double strengthRatio) {
    strength -= (strength*strengthRatio);
}
Noble* Warrior::getEmployer() const { return employer; }
void Warrior::setEmployer(Noble* newEmployer) { 
    employer = newEmployer; 
}
bool Warrior::isHired() const {
    if (employer != nullptr) { return true; }
    else { return false; }
}
void Warrior::runaway() {
    if (employer != nullptr) {
        cout << name << " flees in terror, abandoning his lord, " << employer->getName() << endl;
        employer->lostWarrior(this);
        employer = nullptr;

    }
    else { cout << name << " failed to flee!" << endl; }
}


//
// Noble Implementation Code
//
ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name << " has and army of " << noble.army.size();
    for (size_t i = 0; i < noble.army.size(); ++i) {
        os << "\n    " << *(noble.army[i]);
    }
    return os;
}

/* Constructor */
Noble::Noble(const string& name) : name(name), armyStrength(0), isDead(false) {}

/* Member Functions */

// Find index of warrior within the noble's army
size_t Noble::locateWarrior(const vector<Warrior*>& army, const Warrior& warrior) const {
    for (size_t i = 0; i < army.size(); ++ i) {
    if (army[i] == &warrior) { // if warrior is in army
        return i; // return it's index
    }
    }
    // if warrior not in noble's army
    return army.size(); // return size of army
}

// Hire warrior into noble's army
bool Noble::hire(Warrior& warrior) {
    size_t index = locateWarrior(army, warrior);

    if (( isDead || warrior.getEmployer() != nullptr ) && index == army.size() )
    { // noble is dead or warrior already employed
        cout << name << " failed to hire " << warrior.getName() << endl;
        return false;
    }
    else { // noble alive and warrior unemployed
        Warrior* pWarrior = &warrior;
        army.push_back(pWarrior);
        warrior.setEmployer(this);
        armyStrength += warrior.getStrength();
        return true;
    }
}

// Fire warrior from noble's army
bool Noble::fire(Warrior& warrior) {
    size_t index = locateWarrior(army, warrior);

    if ( isDead || index == army.size() ) {
        cout << name << " failed to fire " << warrior.getName() << endl;
        return false;
    }
    else {
        for (size_t i = index; i < army.size() - 1; ++i) {
            army[i] = army[i+1]; // move each warrior infront back one
        }
        army.pop_back();
        warrior.setEmployer(nullptr);
        armyStrength -= warrior.getStrength();
        cout << warrior.getName() << ", you don't work for me anymore ! -- "
            << name << '.' << endl;
        return true;
    }
}

// Account for warrior running away from noble's army
void Noble::lostWarrior(Warrior* warrior) {
    size_t index = locateWarrior(army, *warrior);

    for (size_t i = index; i < army.size() - 1; ++i) {
            army[i] = army[i+1]; // Move each warrior infront back one
    }
    army.pop_back();
    armyStrength -= warrior->getStrength();
}

// Update strengths of each warrior in noble's army
void Noble::updateStrengths(double strengthRatio) {
    for (size_t i = 0; i < army.size(); ++i) {
        army[i]->updateStrength(strengthRatio);
        armyStrength += army[i]->getStrength();
    }
}

// Account for complete death of noble and all warriors in army
void Noble::die() {
    for (size_t i = 0; i < army.size(); ++i) {
        army[i]->die();
    }
    isDead = true;
}

// Enact a battle between the two chosen nobles
void Noble::battle(Noble& opponent) {
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
const string& Noble::getName() const { return name; }
