#ifndef RENTAL_H
#define RENTAL_H

#include <string>
#include "FleetManager.h"
#include "Payment.h"

using namespace std;

// ==========================================
// Rental System
// Handles drone renting and returns
// ==========================================

class Rental {

private:

    double dailyRate;

public:

    // Constructor
    Rental();

    // Rent drone
    bool rentDrone(FleetManager* fleet, string id, int days, Payment* pay);

    // Return drone
    void returnDrone(FleetManager* fleet, string id);

    // Show rental info
    void showRentals();
};

#endif#pragma once
