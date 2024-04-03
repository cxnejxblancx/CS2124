/*
File: hw02.cpp
Author: Malani Snowden
Purpose: Given a file of commands, as instructed, create warriors, enact battles
         between two chosen warriors, and list all warriors, alive or dead,
         along with their strengths.
*/

//
// Header files; Namespace directive
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


//
// STRUCT
//
struct Warrior {
    // Memeber attributes
    string name;
    int strength;  
};


//
// FUNCTION PROTOTYPES
//
void createWarrior(const string& name, int strength, vector<Warrior>& warriors);
size_t locateWarrior(const string& name, const vector<Warrior>& warriors);
void battle(Warrior& warrior1, Warrior& warrior2);
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
            int strength;

            // Read into 'name' and 'strength'
            file >> name >> strength;

            // Create warrior
            createWarrior(name, strength, warriors);
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
                battle(warrior1, warrior2);
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
void createWarrior(const string& name, int strength, vector<Warrior>& warriors) {
    // Check for warrior with same name
    size_t warriorIndex = locateWarrior(name, warriors);
    if (warriorIndex != warriors.size()) {
        cout << "ERROR: Warrior name already exists!" << endl;
    }
    else{
        // Initialize and instatiate new 'Warrior' object 'newWarrior'
        Warrior newWarrior;
        newWarrior.name = name;
        newWarrior.strength = strength;

        // Add 'newWarrior'  to 'warriors' vector
        warriors.push_back(newWarrior);
    }
}

// Find the location of warrior with same name within 'warriors'
size_t locateWarrior(const string& name, const vector<Warrior>& warriors) {
    // Loop through 'warriors' to find matching name
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i].name == name) { 
            // Return the index of the warrior object if name exists already
            return i;
        }
    }
    // Return the size of 'warriors' if name does not yet exist
    return warriors.size();
}

// Enact a battle b/w the two chosen warriors
void battle(Warrior& warrior1, Warrior& warrior2) {
    cout << warrior1.name << " battles " << warrior2.name << endl;

    // Account for strength differences
    if ((warrior1.strength == 0) && (warrior2.strength == 0)) { // Both dead
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (warrior1.strength == 0) { // ONLY proponent is dead
        cout << "He's dead, " << warrior2.name << endl;
    }
    else if (warrior2.strength == 0) { // ONLY opponent is dead
        cout << "He's dead, " << warrior1.name << endl;
    }
    else { // Neither warrior is dead
        if (warrior1.strength < warrior2.strength) { // Opponent stronger
            warrior2.strength -= warrior1.strength;
            warrior1.strength = 0;
            cout << warrior2.name << " defeats " << warrior1.name << endl;
        }
        else if (warrior1.strength > warrior2.strength) { // Opponent weaker
            warrior1.strength -= warrior2.strength;
            warrior2.strength = 0;
            cout << warrior1.name << " defeats " << warrior2.name << endl;
        }
        else { // Warriors have same strength
            warrior1.strength = 0;
            warrior2.strength = 0;
            cout << "Mutual Annihilation: " << warrior1.name << " and " 
                 << warrior2.name << " die at each other's hands" << endl;
        }
    }
}

// Report the status of each warrior in 'warriors'
void reportStatus(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (size_t i = 0; i < warriors.size(); ++i) {
        cout << "Warrior: " << warriors[i].name << ", " 
             << "strength: " << warriors[i].strength  << endl;
    }
}
