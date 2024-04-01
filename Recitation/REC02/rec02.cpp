/*
    File: rec02.cpp
    Author: Malani Snowden
    Purpose: Sort a file of hydrocarbon formulas
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
struct Hydrocarbon {
    // Member attributes
    int numCarb;
    int numHydro;
    vector<string> names;
       
};


//
// FUNCTION PROTOTYPES
//
void openStream(ifstream& file);
size_t findHydrocarb(int numCarb, int numHydro, const vector<Hydrocarbon>& hydrocarbs); // ints don't need to be const
void insertInfo(const string& name, int numCarb,
                int numHydro, vector<Hydrocarbon>& hydrocarbs);
void fillVector(ifstream& file, vector<Hydrocarbon>&hydrocarbs);
void sortVector(vector<Hydrocarbon>& hydrocarbs);
void displayHydrocarb(const Hydrocarbon& hydrocarb);
void displayVector(const vector<Hydrocarbon>& hydrocarbs);


//
// MAIN
//
int main() {
    // Variables
    ifstream file;
    vector<Hydrocarbon> hydrocarbs;

    // Open file stream; Fill vector from stream; Close file
    openStream(file);
    fillVector(file, hydrocarbs);
    file.close();

    // Display each 'Hydrocarb' object
    cout << "\nUnsorted:" << endl;
    displayVector(hydrocarbs);

    // Sort the hydrocarbon formulas in 'hydrocarbs'
    sortVector(hydrocarbs);

    // Display the sorted 'Hydrocarb' objects
    cout << "\nSorted:" << endl;
    displayVector(hydrocarbs);
}


//
// FUNCTION DEFINITIONS
//

// Open file stream
void openStream(ifstream& file) {
    // Variables
    string fileName;

    // Ask user for file name repeatedly until successful
    cout << "File name? ";
    cin >> fileName;
    file.open(fileName);
    while (!file) {
        cout << "File name? ";
        cin >> fileName;
        file.open(fileName);
    }
}

// Locate the 'Hydrocarbon' object with the same chemical formula
size_t findHydrocarb(int numCarb, int numHydro, const vector<Hydrocarbon>& hydrocarbs) {
    // Find the index of the 'Hydrocarbon' with same # of carbons and hydrogens
    for (size_t i = 0; i < hydrocarbs.size(); ++i) {
        if ((hydrocarbs[i].numCarb == numCarb) && (hydrocarbs[i].numHydro == numHydro)) {
            // Return the index, if the hydrocarb formula exists
            return i;
        }
    }
    // Return the size of the vector if it doesn't exist
    return hydrocarbs.size();
}

// If possible, create new 'Hydrocarbon' object; Add new object to 'hydrocarbs'
void insertInfo(const string& name, int numCarb, int numHydro, vector<Hydrocarbon>& hydrocarbs) {
    // Check if formula already exists is 'hydrocarbs'
    size_t hydroIndex = findHydrocarb(numCarb, numHydro, hydrocarbs);
    if (hydroIndex == hydrocarbs.size()) { // Formula does not exist
        // Initialize and instantiate new 'Hydrocarb' object; Add to 'hydrocarbs'
        Hydrocarbon newHydro;
        newHydro.numCarb = numCarb;
        newHydro.numHydro = numHydro;
        newHydro.names.push_back(name);
        hydrocarbs.push_back(newHydro);
    }
    else { // Formula already exists
        // Add the new name to object's 'names' vector
        hydrocarbs[hydroIndex].names.push_back(name);
    }

}

// Fill vector from file stream
void fillVector(ifstream& file, vector<Hydrocarbon>& hydrocarbs) {
    // Token variables
    string name;
    char element;
    int numCarb;
    int numHydro;

    // Read the formula name, # of carbons, and # of hydrogences; Insert info
    while (file >> name >> element >> numCarb >> element >> numHydro) {
        // Insert information for new 'Hydrocarbon' object into 'hydrocarbs'
        insertInfo(name, numCarb, numHydro, hydrocarbs);
    }

}

// Sort 'hydrocarbs' by the 'numCarb' and then by 'numHydro'
void sortVector(vector<Hydrocarbon>& hydrocarbs) { // Bubble Sort
    for (size_t i = 0; i < hydrocarbs.size(); ++i) {
        for (size_t j = 0; j < hydrocarbs.size() - 1; ++j) {
            if ((hydrocarbs[j].numCarb > hydrocarbs[j + 1].numCarb) || (hydrocarbs[j].numCarb == hydrocarbs[j + 1].numCarb)) {
                swap(hydrocarbs[j], hydrocarbs[j + 1]);
            }
        }
    }
}

// Print the chemical formula and list of names of the 'Hydrocarbon' object
void displayHydrocarb(const Hydrocarbon& hydrocarb) {
    cout << 'C' << hydrocarb.numCarb << 'H' << hydrocarb.numHydro << ' ';
    for (size_t i = 0; i < hydrocarb.names.size(); ++i) {
        cout << hydrocarb.names[i] << ' ';
    }
    cout << endl;
}

// Print each 'Hydrocarbon' object in 'hydrocarbs
void displayVector(const vector<Hydrocarbon>& hydrocarbs) {
    for (size_t i = 0; i < hydrocarbs.size(); ++i) {
        displayHydrocarb(hydrocarbs[i]);
    }
}
