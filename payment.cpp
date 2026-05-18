#include "Payment.h"
#include "ConsoleUI.h"

#include <iostream>

using namespace std;

// ==========================================
// Constructor
// ==========================================

Payment::Payment(double w) {
    wallet = w;
}

// ==========================================
// Get Wallet Balance
// ==========================================

double Payment::getWallet() const {

    return wallet;
}

// ==========================================
// Pay Amount
// ==========================================

bool Payment::pay(double amount) {

    if (wallet >= amount) {

        wallet = wallet - amount;
        return true;
    }

    return false;
}

// ==========================================
// Add Money
// ==========================================

void Payment::addMoney(double amount) {

    wallet = wallet + amount;
}

// ==========================================
// Show Wallet
// ==========================================

void Payment::showWallet() {

    cout << CYAN << BOLD;

    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║        WALLET & PAYMENTS          ║\n";
    cout << "╚════════════════════════════════════╝\n";

    cout << RESET;

    cout << "Current Balance : Rs. " << wallet << endl;
}

// ==========================================
// Buy Drone
// ==========================================

bool Payment::buyDrone(double price) {

    if (pay(price)) {

        cout << GREEN;
        cout << "[SUCCESS] Payment Successful! Drone Purchased.\n";
        cout << RESET;

        return true;
    }

    cout << RED;
    cout << "[ERROR] Insufficient Balance!\n";
    cout << RESET;

    return false;
}
