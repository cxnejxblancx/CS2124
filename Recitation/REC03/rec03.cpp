/*
  Author: Malani Snowden
  File: rec03.cpp
  Purpose: Create accounts and manage transactions as instructed by file commands
*/

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
  string name;
  int accNum;
};


// Task 2
// Define an Account class (use a different name than in Task 1)
class Account2 {
    friend ostream& operator<<(ostream& os, const Account2& rhs);
  // friend ostream& operator<<(ostream& os, const Account2& rhs) {
  //   os << rhs.name << '\t' << rhs.accNum;
  //   return os;
  // }

public:
  Account2(const string& name, int accNum) : name(name), accNum(accNum){}
  
  const string& getName() const {
    return name;
  }
  
  int getAccNum() const {
    return accNum;
  }

private:
  string name;
  int accNum;

};

ostream& operator<<(ostream& os, const Account2& rhs) {
  // os << rhs.getName() << '\t' << rhs.getAccNum();
  os << rhs.name << '\t' << rhs.accNum;
  return os;
}

// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes
class Transaction { // MUST be before Account3 class since Account3 has attribute relying on Transaction class
  friend ostream& operator<<(ostream& os, const Transaction& rhs);

  public:
    Transaction(const string& method, int amount) : method(method), amount(amount) {}

  private:
    string method;
    int amount;
};

ostream& operator<<(ostream& os, const Transaction& rhs) {
  if (rhs.method == "Deposit") {
    os << "deposit";
  }
  else {
    os << "withdrawal";
  }
  os << ' ' << rhs.amount;
  return os;
}


class Account3 {
  friend ostream& operator<<(ostream& os, const Account3& rhs);

public:
  Account3(const string& name, int accNum) : name(name), accNum(accNum) {}

  void deposit(int amount) {
    balance += amount;
    transactions.emplace_back(Transaction("Deposit", amount));
  }

  void withdraw(int amount) {
    if (balance < amount) {
      cout << "Account# " << accNum << " has only " << balance << ". Insufficient withdrawl of " << amount << '.' << endl;
    }
    else {
      balance -= amount;
      transactions.emplace_back(Transaction("Withdraw", amount));
    }
  }

private:
  string name;
  int accNum;
  vector<Transaction> transactions;
  int balance = 0;
};

ostream& operator<<(ostream& os, const Account3& rhs) {
  os << rhs.name << ' ' << rhs.accNum << ':' << endl;
  for (size_t i = 0; i < rhs.transactions.size(); ++i) {
    cout << '\t' << rhs.transactions[i] << endl;
  }
  return os;
}


// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)
class Account4 {
  friend ostream& operator<<(ostream& os, const Account4& rhs);

public:
  
  /* Nested PUBLIC TRANSACTION Class */
  class Transaction2 { 
  friend ostream& operator<<(ostream& os, const Account4::Transaction2& rhs);

  public:
    Transaction2(const string& method, int amount) : method(method), amount(amount) {}

  private:
    string method;
    int amount;
  };

  Account4(const string& name, int accNum) : name(name), accNum(accNum) {}

  void deposit(int amount) {
    balance += amount;
    transactions.emplace_back(Transaction2("Deposit", amount));
  }

  void withdraw(int amount) {
    if (balance < amount) {
      cout << "Account# " << accNum << " has only " << balance << ". Insufficient withdrawl of " << amount << '.' << endl;
    }
    else {
      balance -= amount;
      transactions.emplace_back(Transaction2("Withdraw", amount));
    }
  }

private:
  string name;
  int accNum;
  vector<Transaction2> transactions;
  int balance = 0;
};

ostream& operator<<(ostream& os, const Account4& rhs) {
  os << rhs.name << ' ' << rhs.accNum << ':' << endl;
  for (size_t i = 0; i < rhs.transactions.size(); ++i) {
    cout << '\t' << rhs.transactions[i] << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, const Account4::Transaction2& rhs) {
  if (rhs.method == "Deposit") {
    os << "deposit";
  }
  else {
    os << "withdrawal";
  }
  os << ' ' << rhs.amount;
  return os;
}


// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)
class Account5 {
    /* Nested PRIVATE TRANSACTION Class */
  class Transaction3 { 
    friend ostream& operator<<(ostream& os, const Account5::Transaction3& rhs);

  public:
    Transaction3(const string& method, int amount) : method(method), amount(amount) {}

  private:
    string method;
    int amount;
  };

  friend ostream& operator<<(ostream& os, const Account5::Transaction3& rhs); // MUST be declared AFTER Transaction3 class definition for compiler to access it --> Can't access something that isn't defined

  friend ostream& operator<<(ostream& os, const Account5& rhs);

public:
  Account5(const string& name, int accNum) : name(name), accNum(accNum) {}

  void deposit(int amount) {
    balance += amount;
    transactions.emplace_back(Transaction3("Deposit", amount));
  }

  void withdraw(int amount) {
    if (balance < amount) {
      cout << "Account# " << accNum << " has only " << balance << ". Insufficient withdrawl of " << amount << '.' << endl;
    }
    else {
      balance -= amount;
      transactions.emplace_back(Transaction3("Withdraw", amount));
    }
  }

private:

  // attributes
  string name;
  int accNum;
  vector<Transaction3> transactions;
  int balance = 0;
};

ostream& operator<<(ostream& os, const Account5& rhs) {
  os << rhs.name << ' ' << rhs.accNum << ':' << endl;
  for (size_t i = 0; i < rhs.transactions.size(); ++i) {
    cout << '\t' << rhs.Account5::transactions[i] << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, const Account5::Transaction3& rhs) {
  if (rhs.method == "Deposit") {
    os << "deposit";
  }
  else {
    os << "withdrawal";
  }
  os << ' ' << rhs.amount;
  return os;
}

// ===========================================================
// ===========================================================


int main() {
    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";

    ifstream file("accounts.txt");
    if (!file) {
      cerr << "ERROR: Failed to open 'accounts.txt'!" << endl;
      exit(1);
    }

    vector<Account> accounts;
    string name;
    int accNum;

    while(file >> name >> accNum) {
      Account newAcc;
      newAcc.name = name;
      newAcc.accNum = accNum;
      accounts.push_back(newAcc);
    }

    file.close();

    for (size_t i = 0; i < accounts.size(); ++i) {
      cout <<  accounts[i].name << '\t' << accounts[i].accNum << endl;
    }


    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";

    accounts.clear();
    file.open("accounts.txt");
    if (!file) {
      cerr << "ERROR: Failed to open 'accounts.txt'!" << endl;
      exit(1);
    }

    while(file >> name >> accNum) {
      Account newAcc{name, accNum};
      accounts.push_back(newAcc);
    }

    file.close();

    for (size_t i = 0; i < accounts.size(); ++i) {
      cout <<  accounts[i].name << '\t' << accounts[i].accNum << endl;
    }


    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";

    vector<Account2> accounts2;
    file.open("accounts.txt");
    if (!file) {
      cerr << "ERROR: Failed to open 'accounts.txt'!" << endl;
      exit(1);
    }

    while(file >> name >> accNum) {
      Account2 newAcc(name, accNum);
      accounts2.push_back(newAcc); 
    }

    file.close();

    for (size_t i = 0; i < accounts2.size(); ++i) {
      cout << accounts2[i].getName() << '\t' << accounts2[i].getAccNum() << endl;
    }


    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    for (size_t i = 0; i < accounts2.size(); ++i) {
      cout << accounts2[i] << endl;
    }

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    for (size_t i = 0; i < accounts2.size(); ++i) {
      cout << accounts2[i] << endl;
    }


    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";

    accounts2.clear();
    file.open("accounts.txt");
    if (!file) {
      cerr << "EEROR: Failed to open 'accounts.txt'!" << endl;
      exit(1);
    }
    
    while (file >> name >> accNum) {
      accounts2.push_back(Account2(name, accNum));
    }

    file.close();

    for (size_t i = 0; i < accounts2.size(); ++i) {
      cout << accounts2[i] << endl;
    }

    
    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";

    accounts2.clear();
    file.open("accounts.txt");
    if (!file) {
      cerr << "EEROR: Failed to open 'accounts.txt'!" << endl;
      exit(1);
    }
    
    while (file >> name >> accNum) {
      accounts2.emplace_back(name, accNum);
    }

    file.close();

    for (size_t i = 0; i < accounts2.size(); ++i) {
      cout << accounts2[i] << endl;
    }

    
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";

    file.open("transactions.txt");
    if (!file) {
      cerr << "ERROR: Failed to open 'transactions.txt'!" << endl;
      exit(1);
    }

    vector<Account3> accounts3;
    string command;
    int amount;

    while (file >> command) { // command == "Account"
        if (command == "Account") {
          file >> name >> accNum;
          accounts3.emplace_back(name, accNum);
        }
        else if (command == "Deposit") {
          file >> accNum >> amount;
          accounts3[accounts3.size() - 1].deposit(amount);
        }
        else {
          file >> accNum >> amount;
          accounts3[accounts3.size() - 1].withdraw(amount);
        }
    }

    file.close();

    for (size_t i = 0; i < accounts3.size(); ++i) {
      cout << accounts3[i] << endl;
    }


    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";

    file.open("transactions.txt");
    if (!file) {
      cerr << "ERROR: Failed to open 'transactions.txt'!" << endl;
      exit(1);
    }

    vector<Account4> accounts4;

    while (file >> command) { // command == "Account"
        if (command == "Account") {
          file >> name >> accNum;
          accounts4.emplace_back(Account4(name, accNum));
        }
        else if (command == "Deposit") {
          file >> accNum >> amount;
          accounts4[accounts4.size() - 1].deposit(amount);
        }
        else {
          file >> accNum >> amount;
          accounts4[accounts4.size() - 1].withdraw(amount);
        }
    }

    file.close();

    for (size_t i = 0; i < accounts4.size(); ++i) {
      cout << accounts4[i] << endl;
    }

    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";

    file.open("transactions.txt");
    if (!file) {
      cerr << "ERROR: Failed to open 'transactions.txt'!" << endl;
      exit(1);
    }

    vector<Account5> accounts5;

    while (file >> command) { // command == "Account"
        if (command == "Account") {
          file >> name >> accNum;
          accounts5.emplace_back(name, accNum);
        }
        else if (command == "Deposit") {
          file >> accNum >> amount;
          accounts5[accounts5.size() - 1].deposit(amount);
        }
        else {
          file >> accNum >> amount;
          accounts5[accounts5.size() - 1].withdraw(amount);
        }
    }

    file.close();

    for (size_t i = 0; i < accounts5.size(); ++i) {
      cout << accounts5[i] << endl;
    }
}
