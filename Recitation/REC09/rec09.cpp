#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numberOfPages) : numberOfPages(numberOfPages) {}

    virtual void displayNumPages() const { cout << numberOfPages << endl; }
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages) : PrintedMaterial(numberOfPages) {}
private:
    // unsigned numberOfPages;

};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages) : PrintedMaterial(numberOfPages) {}
private:
    // unsigned numberOfPages;

};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages, unsigned numOfIndexPages) 
        : Book(numberOfPages), numOfIndexPages(numOfIndexPages)  {} 

    void displayNumPages() const {
        cout << "Pages: ";
        PrintedMaterial::displayNumPages();
        cout << "Index pages: " << numOfIndexPages << endl;
    }
private:
    // unsigned numberOfPages;
    unsigned numOfIndexPages;

};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages) : Book(numberOfPages) {} // Book constructor --> PrintedMaterial constructor

private:
    // unsigned numOfPages;

};

// tester/modeler code
int main() {
    TextBook text(20, 10);
    Novel novel(25);
    Magazine mag(30);
    // vector<PrintedMaterial>

    text.displayNumPages();
    novel.displayNumPages();
}
