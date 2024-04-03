/*
  Author: Malani Snowden
  File: rec07.cpp
  Focus: Implement the class Rational, so that the following program works.
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);
void normalize(int* x, int* y);

// Put your Rational class here.
class Rational {
    friend istream& operator>>(istream& is, Rational& rational) {
        int num, denom;
        char slash;
        is >> num >> slash >> denom;

        normalize(&num, &denom);
        rational.numerator = num;
        rational.denominator = denom;

        return is;
    }

    friend ostream& operator<<(ostream& os, const Rational& rational) {
        os << rational.numerator << '/' << rational.denominator;
        return os;
    }

    /* Operator Overloading */
    friend bool operator==(const Rational& lhs, const Rational& rhs) {
        return (lhs.numerator == rhs.numerator ) && (lhs.denominator == rhs.denominator);
    }

    friend bool operator<(const Rational& lhs, const Rational& rhs) {
        return (lhs.numerator / lhs.denominator) < (rhs.numerator / rhs.denominator);
    }

public:
    /* Constructors */
    // Rational() {
    //     numerator = 0;
    //     denominator = 1;
    // }

    // Rational(int integer) {
    //     numerator = integer;
    //     denominator = 1;
    // }

    // Don't use extra constructors above ^^; Just pre-initialize arguments to account for  certain arguments that aren't passed in
    // Rational(int num, int denom) { 
    Rational(int num = 0, int denom = 1) { 
        normalize(&num, &denom);
        numerator = num;
        denominator = denom;
    }

    /* Member Functions */
    Rational& operator+=(const Rational& rhs) {
        int num = (numerator * rhs.denominator) + (rhs.numerator * denominator);
        int denom = rhs.denominator;

        normalize(&num, &denom);
        numerator = num;
        denominator = denom;

        return *this;
    }

    // prefix ++ (++a)
    Rational& operator++() {
        numerator += denominator;
        return *this;
    }
    // postfix ++ (a++)
    Rational operator++(int dummy) {
        Rational original(*this);
        numerator += denominator;
        return original;
    }

    explicit operator bool() const {
        return numerator != 0;
    }

private:
    /* Data Members */
    int numerator, denominator;

};

// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.
Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& rhs); // prefix -- (--a)
Rational& operator--( Rational& rhs,int dummy); // postfix -- (a--)
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why shouldn't it compile?
    // cout << "a-- -- = " << a-- -- << endl;
    // cout << "a = " << a << endl;
    /* 
    shouldn't compile --> stacked POST decrement --> first returns copy --> second takes the copy by reference --> NO!!!
    */


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}


// Any functions that are not members and not friends should have
// their definitions here...

void normalize(int* x, int* y) { // should be a MEMBER FUNCTION  that takes NO arguments
    // Simplify
    int gcd = greatestCommonDivisor(*x, *y);
    *x = (*x) / gcd;
    *y = (*y) / gcd;

    // Negative Cases
    if (*x < 0 || *y < 0) {
        if (*x < 0 && *y < 0) {
            *x = abs(*x);
            *y = abs(*x);
        }
        else if (*y < 0) {
            *x = -(*x);
            *y = abs(*y);
        }
    }
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result += rhs;
    return result;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

Rational& operator--(Rational& rhs) { // prefix -- (--a)
    rhs += -1;
    return rhs;
}

// don't pass by reference --> should not return a REFERENCE to a LOCAL variable that is DESTROYED once the function is complete
Rational operator--(Rational& rhs,int dummy) { // postfix -- (a--)
    Rational result(rhs);
    rhs += -1;
    return result;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}
