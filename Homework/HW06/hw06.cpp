/*
File: hw06.cpp
Author: Malani Snowden
Purpose: Implement class BigUnsigned to represent unsigned integer with infinite
         digits using a vector of integers to store each digit. Operator
         overloading.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//
// BIGUNSIGNED CLASS
//

// Put your class and all function definitions here.
class BigUnsigned {
     friend ostream& operator<<(ostream& os, const BigUnsigned& bigUnsigned) {
          for (size_t i = bigUnsigned.digits.size(); i > 0; --i) {
               os << bigUnsigned.digits[i - 1];
          }
          return os;
     } // Output Operator

     friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          int sumLhs = 0;
          int sumRhs = 0;
          int power1 = 0;
          int power2 = 0;
          for (size_t i = 0; i < lhs.digits.size(); ++i) {
               sumLhs += (lhs.digits[i] * pow(10, power1));
               ++power1;
          }
          for (size_t i = 0; i < rhs.digits.size(); ++i) {
               sumRhs += (rhs.digits[i] * pow(10, power2));
               ++power2;
          }

          if (sumLhs < sumRhs) { return true; }
          else { return false; }
     } // Less Than (<) Operator

     friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          if (lhs.digits.size() == rhs.digits.size()) {
               for (size_t i = 0; i < lhs.digits.size(); ++i) {
                    if (lhs.digits[i] != rhs.digits[i]) { return false; }
               }
               return true;
          }
          return false;
     } // Equivalence Operator

public:
     /* Constructors */
     BigUnsigned(int value = 0) { // integer input
          if (value == 0) {
               digits.push_back(value);
          }
          else{
               while (value > 0) {
                    digits.push_back(value % 10);
                    // value = floor(value / 10);
                    value /= 10;
               }
          }
     }

     BigUnsigned(const string& strDigits) { // string input
          int value = 0;
          if (!('0' <= strDigits[0] && strDigits[0] <= '9')) {
               digits.push_back(0);
          }
          else {
               size_t index = 0;
               while (strDigits[index] == '0') {
                    index++;
               }

               for (size_t i = strDigits.size(); i > index; --i) {
                    if (0 <= strDigits[i-1] - '0' && strDigits[i-1] - '0' <= 9) {
                         digits.push_back(strDigits[i-1] - '0');
                    }
               }
          }
     }

     /* Member Functions --> Operator Overloading */
     BigUnsigned& operator++() { // prefix ++
          // size_t index = digits.size() - 1;
          // if (digits[index] < 9) {
          //      digits[index] += 1;
          // }
          // else {
          //      while(digits[index] == 9) {
          //           digits[index] = 0;
          //           index--;
          //      }
          //      digits[index] += 1;
          // }

          // return *this;
          return *this += 1;
     }

     BigUnsigned operator++(int dummy) { // postfix ++
          BigUnsigned original(*this);

          // size_t index = digits.size() - 1;
          // if (digits[index] < 9) {
          //      digits[index] += 1;
          // }
          // else {
          //      while(digits[index] == 9) {
          //           digits[index] = 0;
          //           index--;
          //      }
          //      digits[index] += 1;
          // }
          original += 1;

          return original;
     }

     BigUnsigned& operator+=(const BigUnsigned& rhs) {
          int carryOver = 0;

          // Account for differences in size of 'digits' vector
          if (digits.size() == rhs.digits.size()) { // same size
               for (size_t i = 0; i < digits.size(); ++i) {
                    if ((digits[i] + rhs.digits[i]) + carryOver > 9) {
                         digits[i] = ((digits[i] + rhs.digits[i] + carryOver) % 10);
                         carryOver = 1;
                    }
                    else {
                         digits[i] += rhs.digits[i] + carryOver;
                         carryOver = 0;
                    }
               }
          }
          else if (digits.size() > rhs.digits.size()) { // lhs bigger than rhs
               for (size_t i = 0; i < rhs.digits.size(); ++i) {
                    if (((digits[i] + rhs.digits[i]) + carryOver) > 9) {
                         digits[i] = ((digits[i] + rhs.digits[i] + carryOver) % 10);
                         carryOver = 1;
                    }
                    else {
                         digits[i] += rhs.digits[i] + carryOver;
                         carryOver = 0;
                    }
               }

               size_t index = rhs.digits.size();
               while (index != digits.size()) {
                    if (digits[index] + carryOver > 9) {
                         digits[index] = 0;
                         carryOver = 1;
                    }
                    else {
                         digits[index] += carryOver;
                         carryOver = 0;
                    }
                    ++index;
               }

               if ((carryOver == 1) && (index == digits.size())) {
                    digits.push_back(1);
               }
          }
          else { // rhs bigger than lhs
               for (size_t i = 0; i < digits.size(); ++i) {
                    if ((digits[i] + rhs.digits[i]) + carryOver > 9) {
                         digits[i] = ((digits[i] + rhs.digits[i] + carryOver) % 10);
                         carryOver = 1;
                    }
                    else {
                         digits[i] += rhs.digits[i] + carryOver;
                         carryOver = 0;
                    }
               }

               size_t index = digits.size();
               while (index != rhs.digits.size()) {
                    if (rhs.digits[index] + carryOver > 9) {
                         digits.push_back(0);
                         carryOver = 1;
                    }
                    else {
                         digits.push_back(rhs.digits[index] + carryOver);
                         carryOver = 0;
                    }
                    ++index;
               }

               if ((carryOver == 1) && (index == rhs.digits.size())) {
                    digits.push_back(1);
               }
          }
          return *this;
     }

     explicit operator bool() const {
          if (digits.size() == 1 && digits[0] == 0) {
               return false;
          }
          return true;
     } // bool operator

private:
     vector<int> digits;
};


//
// FUNCTION PROTOTYPES --> Operator Overloading
//
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs); // Addition
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs); // Greater than
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs); // Greater than / Equal to
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs); // Less than / Equal to
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs); // Not equal to


//
// MAIN
//
int main() {
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;
    
    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b 
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;
    
    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;
         
    
    BigUnsigned big("987654321");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
}


//
// FUNCTION DEFINITIONS --> Operator Overloading
//
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     BigUnsigned result(lhs);
     result += rhs;
     return result;
} // Addition operator

bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs < rhs) && !(lhs == rhs);
} // Greater than operator

bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs < rhs);
} // Greater than/Equal to operator

bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs > rhs);
} // Less than/Equal to operator

bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs == rhs);
} // Not equal to operator
