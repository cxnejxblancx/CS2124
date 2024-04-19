/*
Author: Malani Snowden
File: rec12.cpp
Focus: Implement a DoublyLinkedList Class
*/

// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& list) {
        if (list.header != nullptr) {
            Node* curr = list.header->next;
            while (curr != list.trailer) {
                os << curr->data << ' ';
                curr = curr->next;
            }
        }
        return os;
    }

private: 
    /* Private Nested Class - NODE */
    struct Node {
        Node(int data = 0, Node* next = nullptr, Node* prior = nullptr)
            : data(data), next(next), prior(prior) {}
        int data;
        Node* next;
        Node* prior;
    };

public:
    /* Task 8 - COPY CONTROL (OPTIONAL) */
    List(const List& rhs) {
        header = new Node{};
        trailer = new Node{0, nullptr, header};
        Node* curr = rhs.header->next;
        while(curr != rhs.trailer) {
           push_back(curr->data);
           curr = curr->next;
        }
        theSize = rhs.theSize;

    } // Copy Constructor
    ~List() {
        clear();
        delete header;
        delete trailer;
    } // Destructor
    List& operator=(const List& rhs) {
        if (this != &rhs) {
            clear();
            delete header;
            delete trailer;
            header = new Node{};
            trailer = new Node{0, nullptr, header};
            theSize = rhs.theSize;
            Node* curr = rhs.header;
            while( curr != rhs.trailer) {
                push_back(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    } // Assignment Operator


    /* Task One */
    List() : theSize(0) {
        header = new Node{};
        trailer = new Node{0, nullptr, header};
        header->next = trailer;
    }

    void push_back(int data) {
        Node* newNode = new Node{data, trailer, trailer->prior};
        trailer->prior->next = newNode;
        trailer->prior = newNode;
        ++theSize;
    }

    void pop_back() {
        if (theSize == 0) { cout << "ERROR: List is empty!" << endl; }
        else {
            Node* last = trailer->prior;
            Node* secondToLast = trailer->prior->prior;
            secondToLast->next = trailer;
            trailer->prior =secondToLast;
            delete last;
            --theSize;
        }
    }

    int& front() { return header->next->data; }
    int front() const { return header->next->data; }

    int& back() { return trailer->prior->data; }
    int back() const { return trailer->prior->data; }

    size_t size() const { return theSize; }

    /* Task Two */
    void push_front(int data) {
        Node* newNode = new Node{data, header->next, header};
        header->next->prior = newNode;
        header->next = newNode;
        ++theSize;
    }

    void pop_front() {
        if (theSize == 0) { cout << "ERROR: List is empty!" << endl; }
        else {
            Node* first = header->next;
            Node* second = header->next->next;
            second->prior = header;
            header->next = second;
            delete first;
            --theSize;
        }
    }

    /* Task 3 */
    void clear() {
        while (theSize != 0) { 
            pop_back();
        }
    }

    /* Task 4 */
    int& operator[](size_t index) { // allows for modification of list
        if (index < 0 || index >= theSize) { cerr << "ERROR: Invalid index!" << endl; }
        Node* target = header->next;
        size_t i = 0;
        while (i < index) { // stops once i = index (target = list[index])
            target = target->next;
            ++i;
        }
        return target->data;
    }

    int operator[](size_t index) const { // allows basic viewing access of list 
        if (index < 0 || index >= theSize) { cerr << "ERROR: Invalid index!" << endl; }
        Node* target = header->next;
        size_t i = 0;
        while (i < index) { // stops once i = index (target = list[index])
            target = target->next;
            ++i;
        }
        return target->data;
    }

    /* Task 5 */
    class iterator {
        /* Task 6 */
        friend class List;

        friend bool operator==(const iterator& lhs, const iterator& rhs)  {
            return lhs.ptrNode == rhs.ptrNode;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return lhs.ptrNode != rhs.ptrNode;
        }
    public:
        iterator(Node* node) : ptrNode(node) {}

        iterator operator++() { // pointer arithmetic 
            if (ptrNode->next != nullptr) {
                ptrNode = ptrNode->next;
            }
            return *this;
        }
        iterator operator--() {
            if (ptrNode->prior != nullptr) {
                ptrNode = ptrNode->prior;
            }
            return *this;
        }   

        int& operator*() const {
            return ptrNode->data;
        }
    private:
        Node* ptrNode;
    };

    iterator begin() const { return iterator(header->next); }
    iterator end() const { return iterator(trailer); }

    /* Task 6 */
    iterator insert(iterator iter, int data) {
        Node* curr = iter.ptrNode;
        Node* newNode = new Node{data, curr, curr->prior};
        curr->prior->next = newNode;
        curr->prior = newNode;
        ++theSize;
        return iter;
    }


/* Task 7 */
iterator erase(iterator iter) {
    if (theSize == 0) {
        cout << "ERROR: List is empty!" << endl;
        return nullptr;
    }
    else if (iter == nullptr) {
        return iter;
    }
    if (iter == begin()) {
        pop_front();
    }
    else {
        Node* deleteNode = iter.ptrNode;
        Node* prev = deleteNode->prior;
        Node* following = deleteNode->next;
        prev->next = following;
        following->prior = prev;

        iter.ptrNode = following;
        delete deleteNode;
        --theSize;
    }
    return iter;
}

private:
    /* data members */
    size_t theSize;
    Node* header;
    Node* trailer;
};

// Task 1
void printListInfo(const List& myList) {
        // cout << "size: " << myList.size()
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    // for (size_t i = 0; i < myList.size(); ++i) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << "Leaving doNothing\n";
}    

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
