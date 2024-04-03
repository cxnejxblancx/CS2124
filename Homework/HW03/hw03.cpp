/*
File: hw03.cpp
Author: Malani Snowden
Purpose: Given a file of commands, as instructed, create warriors, enact battles
         between two chosen warriors, and list all warriors, alive or dead,
         along with their weapon and their weapon's strength.
*/


//
// HEADER FILES; NAMESPACE DIRECTIVE
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


//
// CLASS
//
class Warrior {
    /* Nested private WEAPON class */
    class Weapon{
        friend ostream& operator<<(ostream& os, const Weapon& weapon) {
            os << "weapon: " << weapon.name << ", " << weapon.strength;
            return os;
        }

    public:
        /* Weapon Constructor */
        Weapon(const string& name, int strength) : name(name), strength(strength) {}

        /* Getters and Setters */
        int getStrength() const { return strength; }
        void setStrength(int newStrength) { 
            strength = newStrength;
        }

    private:
        /* Member Variables */
        string name;
        int strength;
    };

    friend ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << "Warrior: " << warrior.name << ", " << warrior.weapon;
        return os;
    }

public:
    /* Warrior Constructor */
    Warrior(const string& name, const string& weapName, int weapStrength) : 
        name(name), weapon(weapName, weapStrength) {}

    /* Member Function */

    // Enact a battle b/w the two chosen warriors
    void battle(Warrior& opponent) { 
        cout << name << " battles " << opponent.getName() << endl;

        // Account for strength differences
        if ((getStrength() == 0) && (opponent.getStrength() == 0)) { // Both dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (getStrength() == 0) { // ONLY proponent is dead
            cout << "He's dead, " << opponent.getName() << endl;
        }
        else if (opponent.getStrength() == 0) { // ONLY opponent is dead
            cout << "He's dead, " << name << endl;
        }
        else { // Neither warrior is dead
            if (getStrength() < opponent.getStrength()) { // Opponent stronger
                opponent.setStrength(opponent.getStrength() - getStrength());
                setStrength(0);
                cout << opponent.getName() << " defeats " << name << endl;
            }
            else if (getStrength() > opponent.getStrength()) { // Opponent weaker
                setStrength(getStrength() - opponent.getStrength());
                opponent.setStrength(0);
                cout << name << " defeats " << opponent.getName() << endl;
            }
            else { // Warriors have same strength
                setStrength(0);
                opponent.setStrength(0);
                cout << "Mutual Annihilation: " << name << " and " 
                    << opponent.getName() << " die at each other's hands" << endl;
            }
        }
    }

    /* Getters and Setters */
    const string& getName() const { return name; }
    int getStrength() const { return weapon.getStrength(); }
    void setStrength(int newStrength) {
        weapon.setStrength(newStrength);
    }

private:
    /* Member Variables */
    string name;
    Weapon weapon;
};


//
// FUNCTION PROTOTYPES --> Must be after Warrior class (use of vector<Warrior>)
//
void createWarrior(const string& name, const string& weapName, int weapStrength, 
    vector<Warrior>& warriors);
size_t locateWarrior(const string& name, const vector<Warrior>& warriors);
void reportStatus(const vector<Warrior>& warriors);


//
// MAIN
//
int main() {
    // Open 'warriors.txt'
    ifstream file("warriors.txt");

    // Ensure successful file opening
    if (!file) {
        cerr << "ERROR: Failed to open 'warriors.txt'!" << endl;
        exit(1);
    }

    // Variables
    vector<Warrior> warriors;
    string command;

    // Loop through file based on different commands
    while (file >> command) {
        // Account for different commands
        if (command == "Warrior") {
            // Token variables
            string name;
            string weapName;
            int weapStrength;

            // Read into 'name' and 'strength'
            file >> name >> weapName >> weapStrength;

            // Create warrior
            createWarrior(name, weapName, weapStrength, warriors);
        }
        else if (command == "Battle") {
            // Token variables
            string name1;
            string name2;

            // Read warrior names into 'warrior1' and 'warrior2'
            file >> name1 >> name2;

            // Ensure existence of each warrior; Enact battle if warriors exist
            size_t index1 = locateWarrior(name1, warriors);
            size_t index2 = locateWarrior(name2, warriors);
            if ((index1 == warriors.size()) || (index2 == warriors.size())) { 
                // Display error message if warrior
                cout << "ERROR: One or both warriors are undefined!" << endl;
            }
            else { 
                // Have the located warrior objects battle
                Warrior& warrior1 = warriors[index1];
                Warrior& warrior2 = warriors[index2];
                warrior1.battle(warrior2);
            }
        }
        else { // command == "Status"
            reportStatus(warriors);
        }
    }

    // Close file
    file.close();
}


//
// FUNCTION DEFINITIONS
//

// Initialize new 'Warrior' object; Add warrior to 'warriors' (If new name)
void createWarrior(const string& name, const string& weapName, int weapStrength, 
    vector<Warrior>& warriors) {
    // Check for warrior with same name
    size_t warriorIndex = locateWarrior(name, warriors);
    if (warriorIndex != warriors.size()) {
        cout << "ERROR: Warrior name already exists!" << endl;
    }
    else{
        // Instatiate 'Warrior' object 'newWarrior'; Emplace back onto 'warriors'
        warriors.emplace_back(name, weapName, weapStrength);
    }
}

// Find the location of warrior with same name within 'warriors'
size_t locateWarrior(const string& name, const vector<Warrior>& warriors) {
    // Loop through 'warriors' to find matching name
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i].getName() == name) {  // name already exists
            // Return the index of the existing warrior object
            return i;
        }
    }
    // Return the size of 'warriors' if name does not yet exist
    return warriors.size();
}

// Report the status of each warrior in 'warriors'
void reportStatus(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (size_t i = 0; i < warriors.size(); ++i) {
        cout << warriors[i] << endl;
    }
}
