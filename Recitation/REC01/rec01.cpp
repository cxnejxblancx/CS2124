/*
  rec01_start.cpp
  spring 2024
*/

// Header files; Namespace directive
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//
// Function prototypes for tasks 15-17
//

// Task 15. Function to display a vector of ints
void displayInts(const vector<int>& ints);

// Task 16. Function to modify the vector, using indices
void doubleInts(vector<int>& ints);

// Task 17. Function to modify the vector, using a ranged for
void doubleRangedFor(vector<int>& ints);


//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "Hello, World!" << std::endl;
  
    // Task 2  Printing hello ...  Using "using namespace"
    cout << "Hello, World!" << endl;


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << "x: " << x << endl; // UNDEFINED
    
    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << "Sizeof(x): " << sizeof(x) << endl
         << "Sizeof(y): " << sizeof(y) << endl
         << "Sizeof(z): " << sizeof(z) << endl
         << "Sizeof(pie): " << sizeof(pie) << endl;
    
    // Task 5  Attempt to assign the wrong type of thing to a variable
    // x = "felix";       --> COMPILATION ERROR


    //
    // Conditions
    //

    // Task 6  Testing for a range
    if ((y >= 10) && (y <= 20)) { cout << "Yes, y is between 10 and 20" << endl; }
    else { cout << "No, y is not between 10 annd 20" << endl; }
    

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (int i = 10; i <= 20; ++i) {
      cout << i << ' ';
    }
    cout << endl;

    // Then with a while loop
    int i = 10;
    while (i <= 20) {
      cout << i << ' ';
      ++i;
    }
    cout << endl;

    // Finally with a do-while loop
    i = 10;
    do {
      cout << i << ' ';
      ++i;
    } while (i <= 20);
    cout << endl;


    // Task 8  Looping to successfully open a file, asking user for the name
    string fileName;
    cout << "File Name: ";
    cin >> fileName;
    ifstream ifs(fileName);
    while (!ifs) {
      cout << "File Name: ";
      cin >> fileName;
      ifs.open(fileName);
    }

    // Task 9  Looping, reading file word by "word".
    string word;
    while (ifs >> word) {
      cout << word << endl;
    }
    ifs.close();

    // Task 10 Open a file of integers, read it in, and display the sum.
    int sum = 0;
    int num;
    ifs.open("integers.txt");
    while (!ifs) {
      cerr << "ERROR: 'integers.txt' could not be opened!" << endl;
      exit(1);
    }
    while (ifs >> num) {
      sum += num;
    }
    ifs.close();
    cout << "Sum: " << sum << endl;

    // Taks 11 Open and read a file of integers and words. Display the sum.
    ifs.open("mixed.txt");
    while (!ifs) {
      cerr << "ERROR: 'mixed.txt' could not be opened!" << endl;
      exit(1);
    }
    sum = 0;
    while (ifs >> num) {
      sum += num; // stops finding ints once it reaches the first string
    }
    ifs.close();
    cout << "Sum: " << sum << endl; 


    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> even_ints;
    for (size_t i = 10; i <= 100; ++++i) {
      even_ints.push_back(i);
    }

    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t i = 0; i < even_ints.size(); ++i) {
      cout << even_ints[i] << ' ';
    }
    cout << endl;

    //         b) using a "ranged for"
    for (int integer : even_ints) {
      cout << integer << ' ';
    }
    cout << endl;

    //         c) using indices again but backwards
    for (size_t i = even_ints.size(); i > 0; --i) {
      cout << even_ints[i - 1] << ' ';
    }
    cout << endl;

    // Task 14. Initialize a vector with the primes less than 20. 
    vector<int> primes { 2, 3, 5, 7, 11, 13, 17, 19};
    for (int prime : primes) {
      cout << prime << ' ';
    }
    cout << endl;


    //
    // Function calls
    //

    vector<int> ints { 1, 2, 3, 4, 5 };

    // Task 15  Function to print a vector 
    displayInts(ints);


    // Task 16  Function to double the values in a vector
    doubleInts(ints);


    // Task 17  Function to double the values in a vector, using a ranged for 
    doubleRangedFor(ints);

}


//
// Function definitions for tasks 15-17
//

// Task 15. Function to display a vector of ints
void displayInts(const vector<int>& ints) {
  for (size_t i = 0; i < ints.size(); ++i) {
    cout << ints[i] << ' ';
  }
  cout << endl;
}

// Task 16. Function to modify the vector, using indices
void doubleInts(vector<int>& ints) {
  for (size_t i = 0; i < ints.size(); ++i) {
    ints[i] *= 2;
  }
  displayInts(ints);
}

// Task 17. Function to modify the vector, using a ranged for
void doubleRangedFor(vector<int>& ints) {
  for (int& integer : ints) { // must be a REFERENCE --> directly alter each int
    integer *= 2;
  }
  displayInts(ints);
}
