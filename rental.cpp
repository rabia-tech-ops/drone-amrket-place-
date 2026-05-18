#include "Rental.h"
#include "ConsoleUI.h"

#include <iostream>

using namespace std;

// ==========================================
// Constructor
// ==========================================

Rental::Rental() {

    dailyRate = 5000;
}

// ==========================================
// Rent Drone
// ==========================================

bool Rental::rentDrone(
    FleetManager* fleet,
    string id,
    int days,
    Payment* pay
) {

    Drone* d = fleet->findById(id);

    if (d == NULL) {

        cout << RED;
        cout << "Drone not found.\n";
        cout << RESET;

        return false;
    }

    if (d->getStatus() != "Available") {

        cout << RED;
        cout << "Drone not available.\n";
        cout << RESET;

        return false;
    }

    double cost = dailyRate * days;

    if (pay->pay(cost)) {

        d->setStatus("Rented");

        cout << GREEN;

        cout << "[SUCCESS] Drone Rented Successfully!\n";
        cout << "Drone  : " << d->getName() << endl;
        cout << "Days   : " << days << endl;
        cout << "Cost   : Rs." << cost << endl;

        cout << RESET;

        return true;
    }

    cout << RED;
    cout << "Not Enough Wallet Balance!\n";
    cout << RESET;

    return false;
}

// ==========================================
// Return Drone
// ==========================================

void Rental::returnDrone(
    FleetManager* fleet,
    string id
) {

    Drone* d = fleet->findById(id);

    if (d != NULL) {

        d->setStatus("Available");

        cout << GREEN;
        cout << "Drone Returned Successfully!\n";
        cout << RESET;
    }
    else {

        cout << RED;
        cout << "Invalid Drone ID!\n";
        cout << RESET;
    }
}

// ==========================================
// Show Rentals
// ==========================================

void Rental::showRentals() {

    cout << CYAN;

    cout << "\n================================\n";
    cout << "       RENTAL SYSTEM INFO       \n";
    cout << "================================\n";

    cout << RESET;

    cout << "Daily Rate : Rs." << dailyRate << endl;
}
