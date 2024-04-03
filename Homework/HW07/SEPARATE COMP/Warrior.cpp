/*
File: Noble.cpp
Author: Malani Snowden
Purpose: Warrior class implementation code
*/

#include "Warrior.h"
#include "Noble.h"
#include <iostream> // optional
#include <vector> // optional
#include <string> // optional
using namespace std;

namespace WarriorCraft {
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
        if ( employer != nullptr ) {
            cout << name << " flees in terror, abandoning his lord, " << employer->getName() << endl;
            employer->lostWarrior(this);
            employer = nullptr;

        }
        else { cout << name << " failed to flee!" << endl; }
    }
}