ifndef PAYMENT_H
#define PAYMENT_H

using namespace std;

// ==========================================
// Payment Class
// Handles wallet and transactions
// ==========================================

class Payment {

private:

    double wallet;

public:

    // Constructor
    Payment(double w = 0);

    // Get wallet balance
    double getWallet() const;

    // Deduct payment
    bool pay(double amount);

    // Add money
    void addMoney(double amount);

    // Show wallet UI
    void showWallet();

    // Buy drone
    bool buyDrone(double price);
};

#endif#pragma once
