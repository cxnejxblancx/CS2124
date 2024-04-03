/*
File: Noble.cpp
Author: Malani Snowden
Purpose: Noble class implementation code
*/

#include "Noble.h"
#include "Warrior.h"
#include <iostream> // optional
#include <vector> // optional
#include <string> // optional
using namespace std;

namespace WarriorCraft {
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
                army[i] = army[i+1]; // move each warrior infront back one
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
}