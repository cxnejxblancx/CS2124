/*
File: Noble.h
Author: Malani Snowden
Purpose: Noble class header file
*/

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    /* Forward class declaration */
    class Warrior;

    /* NOBLE Class */
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);

    public:
        /* Constructor */
        Noble(const std::string& name);
            
        /* Member Functions */

        // Find index of warrior within the noble's army
        size_t locateWarrior(const std::vector<Warrior*>& army, const Warrior& warrior) const;

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
        const std::string& getName() const;

    private:
        /* member attributes */
        std::string name;
        std::vector<Warrior*> army;
        double armyStrength;
        bool isDead;
    };
}

#endif