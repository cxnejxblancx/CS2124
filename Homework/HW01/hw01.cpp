/*
File: hw01.cpp
Author: Malani Snowden
Purpose: Reverse and decrypt text in a file that has been encrypted by a caesar cypher
         based on the rotation distance (encryption key) in the first line of the file
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
// FUNCTION PROTOTYPES
//
void decryptLine(string& line, const int rotationDist);
void decryptChar(char& character, const int rotationDist);


//
// MAIN
//
int main() {
    // Open file 'encrypted.txt'
    ifstream file("encrypted.txt");

    // Check for successful file opening
    while (!file) {
        cerr << "ERROR: 'encrypted.txt' could not be opened!" << endl;
        exit(1);
    }

    // Variables
    int rotationDist;
    vector<string> lines;
    string line;

    // Read first line in file into 'rotationDist
    file >> rotationDist;
    rotationDist %= 26; // Account for rotation distances >/= 26 or </= -26
    
    // Ignore first line of file; Place lines of file into 'lines'
    getline(file, line);
    while (getline(file, line)) {
        lines.push_back(line);
    }

    // Loop through 'lines' in reverse; Decrypt and print each line
    if (rotationDist != 0) {
        for (size_t i = lines.size(); i > 0; --i) {
            decryptLine(lines[i - 1], rotationDist);
            cout << lines[i - 1] << endl;
        }
    }
}


//
// FUNCTION DEFINITIONS
//

// Decrypt each line in file
void decryptLine(string& line, const int rotationDist) {
    for (size_t i = 0; i < line.size(); ++i) {
        if ((line[i] >= 'A') && (line[i] <= 'Z')) {
            decryptChar(line[i], rotationDist);
        }
    }
}

// Decrypt each character in a line
void decryptChar(char& character, const int rotationDist) {
    if (rotationDist < 0) { // Decrypt forward
        if ((character - rotationDist) <= 'Z') {
            character -= rotationDist;
        }
        else {
            int distFromA = (-rotationDist) - ('Z' - character) - 1;
            character = 'A' + distFromA;
        }
    }
    else { // Decrypt backward
        if ((character - rotationDist) >= 'A') {
            character -= abs(rotationDist);
        }
        else {
            int distFromZ = rotationDist - (character - 'A') - 1;
            character = 'Z' - distFromZ;
        }
    }
}
