/*
    Author: Malani Snowden
    File: rec10.cpp
    Focus: Practice inheritance with implementation of abstract classes
*/

//
// HEADER FILES; NAMESPACE DIRECTIVE
//
#include <iostream>
#include <vector>
using namespace std;



//
// INSTRUMENT (Base/Parent) Class
//
class Instrument {
    friend ostream& operator<<(ostream& os, const Instrument& instr) {
        instr.displayInstr();
        return os;
    }
public:
    // Play the instrument's unique sound
    virtual void play() = 0; // Abstract

    // Account for different ways to play each type of instrument
    virtual void makeSound() = 0; // Abstract

    // Display each type of instrument
    virtual void displayInstr() const {}
private:
};

void Instrument::makeSound() {
    cout << "To make a sound... ";
}


/* BRASS (Derived/Child) Class */
class Brass : public Instrument {
public:
    Brass(unsigned mpSize) : mpSize(mpSize) {}
protected:
    void makeSound() {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mpSize << endl;
    }
    void displayInstr() const { cout << mpSize; }
private:
    unsigned mpSize;
};

/* STRING (Derived/Child) Class */
class String : public Instrument {
public:
    String(unsigned pitch) : pitch(pitch) {}
protected:
    void makeSound() {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
    void displayInstr() const { cout << pitch; }
private:
    unsigned pitch;
};

/* PERCUSSION (Derived/Child) Class */
class Percussion : public Instrument {
public:
    Percussion() {};
protected:
    void makeSound() {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
private:
};


/* DRUM (Derived/Grandchild) Class */
class Drum : public Percussion {
public:
    Drum() : Percussion() {};
    void displayInstr() const {
        cout << "Drum";
    }
    void play() { cout << "Boom"; }
};

/* CYMBAL (Derived/Grandchild) Class */
class Cymbal : public Percussion {
public:
    Cymbal() : Percussion() {};
    void displayInstr() const {
        cout << "Cymbal";
    }
    void play() { cout << "Crash"; }
};

/* CELLO (Derived/Grandchild) Class */
class Cello : public String {
public:
    Cello(unsigned pitch) : String(pitch) {}
    void displayInstr() const {
        cout << "Cello: ";
        String::displayInstr();
    }
    void play() { cout << "Squawk"; }
};

/* VIOLIN (Derived/Grandchild) Class */
class Violin : public String {
public:
    Violin(unsigned pitch) : String(pitch) {}
    void displayInstr() const {
        cout << "Violin: ";
        String::displayInstr();
    }
    void play() { cout << "Screech"; }
};

/* TROMBONE (Derived/Grandchild) Class */
class Trombone : public Brass {
public:
    Trombone(unsigned mpSize) : Brass(mpSize) {}
    void displayInstr() const {
        cout << "Trombone: ";
        Brass::displayInstr();
    }
    void play() { cout << "Blat"; }
};

/* TRUMPET (Derived/Grandchild) Class */
class Trumpet : public Brass {
public:
    Trumpet(unsigned mpSize) : Brass(mpSize) {}
    void displayInstr() const {
        cout << "Trumpet: ";
        Brass::displayInstr();
    }
    void play() { cout << "Toot"; }
};



//
// MILL Class
//
class MILL {
    friend ostream& operator<<(ostream& os, const MILL& mill) {
        os << "The MILL has the following instruments:";
        if (mill.instrs.size() != 0) {
            for (size_t i = 0; i < mill.instrs.size(); ++i) {
                if (mill.instrs[i] != nullptr) {
                    os << "\n    " << *(mill.instrs[i]);
                }
            }
        }
        else {
            os << " None";
        }
        return os;
    }
public:
    MILL() {}

    // Accept an instrument into the MILL
    void receiveInstr(Instrument& instr) {
        // Test instrument by making a sound
        instr.makeSound();

        // Place instrument in the FIRST available opening
        size_t openIndex = instrs.size();
        for (size_t i = instrs.size(); i > 0; --i) {
            if (instrs[i - 1] == nullptr) { openIndex = i - 1; }
        }
        if (openIndex == instrs.size()) { instrs.push_back(&instr); }
        else { instrs[openIndex] = &instr; }
    }

    // Test each instrument in the MILL to see if it is working
    void dailyTestPlay() {
        for (size_t i = 0; i < instrs.size(); ++i) {
            if (instrs[i] != nullptr) { instrs[i]->makeSound(); }
        }
    }

    // Return the next available instrument in the MILL --> To later be loaned to a musician
    Instrument* loanOut() {
        size_t index = 0;
        while (instrs[index] == nullptr && index != instrs.size()) {
            ++index;
        }
        if (index != instrs.size()) {
            Instrument* instr = instrs[index];
            instrs[index] = nullptr;
            return instr; 
        }
        else { return nullptr; }
    }

private:
    vector<Instrument*> instrs;
};



// 
// Musician class as provided to the students. Requires an Instrument class.
// 
class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};



//
// ORCH Class --> Emulate an orchestra of musicians
//
class Orch {
public:
    // Add a new musician to the orchestra
    void addPlayer(Musician& musician) { orch.push_back(&musician); }

    // Allow the musicians to play their instruments' unique sound
    void play() {
        for (size_t i = 0; i < orch.size(); ++i) {
            if (orch[i] != nullptr) {
                orch[i]->play();
            }
        }
        cout << endl;
    }
private:
    vector<Musician*> orch;
};



int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);
  
    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";
  
    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();


    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    groucho.testPlay();	
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
       mill.dailyTestPlay();
  
    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;



    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";
    
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //cout << endl << mill << endl;
}
