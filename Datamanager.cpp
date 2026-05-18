#include "DataManager.h"
#include "ConsoleUI.h"

#include <iostream>

using namespace std;

// ==========================================
// Constructor
// ==========================================

DataManager::DataManager(AuthManager* a, FleetManager* f) {

    auth = a;
    fleet = f;
}

// ==========================================
// Marketplace Reports
// ==========================================

void DataManager::showReports() {

    cout << CYAN << BOLD;

    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║      MARKETPLACE ANALYTICS        ║\n";
    cout << "╚════════════════════════════════════╝\n";

    cout << RESET;

    cout << "Total Customers : "
        << auth->getTotalCustomers() << endl;

    cout << "Total Drones    : "
        << fleet->getDroneCount() << endl;

    cout << "Orders Completed: 240\n";
    cout << "Revenue Earned  : Rs.12,000,000\n";
    cout << "Top Drone       : SkyCam Pro\n";
    cout << "Best Category   : Delivery Drones\n";
}

// ==========================================
// Show Registered Customers
// ==========================================

void DataManager::showUsers() {

    cout << YELLOW << BOLD;
    cout << "\n========== REGISTERED CUSTOMERS ==========\n";
    cout << RESET;

    CustomerAccount* list = auth->getAllCustomers();

    int total = auth->getTotalCustomers();

    for (int i = 0; i < total; i++) {

        cout << "\nCustomer " << i + 1 << endl;

        cout << "Name   : "
            << list[i].name << endl;

        cout << "Wallet : Rs."
            << list[i].wallet << endl;

        cout << "VIP    : "
            << list[i].vip << endl;
    }
}
