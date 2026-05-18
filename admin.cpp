#include "Admin.h"
#include "ConsoleUI.h"
#include <iostream>

using namespace std;

// ==========================================
// Constructor
// ==========================================

Admin::Admin(string n, string i, FleetManager* f, DataManager* d)
    : Person(n, i, "Administrator")
{
    fleet = f;
    data = d;
}

// ==========================================
// Display Admin Information
// ==========================================

void Admin::displayInfo() {
    cout << CYAN
        << "Admin : " << name
        << " | Role : " << role
        << RESET << endl;
}

// ==========================================
// Show Admin Control Panel
// ==========================================

void Admin::showPanel() {

    cout << MAGENTA << BOLD;

   
    

    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║         ADMIN CONTROL PANEL          ║\n";
    cout << "╚══════════════════════════════════════╝\n";

    cout << RESET;

    displayInfo();
}

// ==========================================
// Add Drone
// ==========================================

void Admin::addDrone() {
    fleet->addDroneMenu();
}

// ==========================================
// Remove Drone
// ==========================================

void Admin::removeDrone() {
    fleet->removeDroneMenu();
}

// ==========================================
// View Reports
// ==========================================

void Admin::viewReports() {
    data->showReports();
}

// ==========================================
// View Users
// ==========================================

void Admin::viewUsers() {
    data->showUsers();
}

// ==========================================
// Manage Marketplace
// ==========================================

void Admin::manageMarketplace() {
    fleet->showTable();
}
