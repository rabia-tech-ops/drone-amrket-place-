#include "Person.h"

using namespace std;

// ==========================================
// Constructor
// ==========================================

Person::Person(string n, string i, string r) {

    name = n;
    id = i;
    role = r;
}

// ==========================================
// Getters
// ==========================================

string Person::getName() const {

    return name;
}

string Person::getId() const {

    return id;
}

string Person::getRole() const {

    return role;
}

// ==========================================
// Setter
// ==========================================

void Person::setName(string n) {

    name = n;
}
