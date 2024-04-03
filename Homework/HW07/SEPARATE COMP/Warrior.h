/*
File: Warrior.h
Author: Malani Snowden
Purpose: Warrior class header file
*/

#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    /* Forward class declaration */
    class Noble;

    /* WARRIOR Class */
    class Warrior { 
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
    public:
        /* Constructor */
        Warrior(const std::string& name, int strength);

        /* Member Functions */
        void die();

        /* Getters and Setters(Modifiers) */
        const std::string& getName() const;
        double getStrength() const;
        void updateStrength(double strengthRatio);
        Noble* getEmployer() const;
        void setEmployer(Noble* newEmployer);
        bool isHired() const;
        void runaway();

    private:
        /* Member attributes */
        std::string name;
        double strength;
        Noble* employer;
    };
}

#endif