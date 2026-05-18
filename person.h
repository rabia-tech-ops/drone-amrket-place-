#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

// ==========================================
// Abstract Base Class: Person
// Common user information
// ==========================================

class Person {

protected:

    string name;
    string id;
    string role;

public:

    // Constructor
    Person(string n = "", string i = "", string r = "");

    // Pure virtual function
    virtual void displayInfo() = 0;

    // Virtual destructor
    virtual ~Person() {
    }

    // Getters
    string getName() const;
    string getId() const;
    string getRole() const;

    // Setter
    void setName(string n);
};

#endif
