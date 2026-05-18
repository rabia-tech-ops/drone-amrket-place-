#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include "FleetManager.h"
#include "DataManager.h"

using namespace std;

// ==========================================
// Admin Class
// Derived from Person
// Handles marketplace management
// ==========================================

class Admin : public Person {
private:
    FleetManager* fleet;
    DataManager* data;

public:

    // Constructor
    Admin(string n, string i, FleetManager* f, DataManager* d);

    // Display admin information
    void displayInfo();

    // Show admin dashboard
    void showPanel();

    // Marketplace functions
    void addDrone();
    void removeDrone();
    void viewReports();
    void viewUsers();
    void manageMarketplace();
};

#endif
