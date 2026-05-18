#include "DeliveryDrone.h"

#include <iostream>

using namespace std;

// ==========================================
// Constructor
// ==========================================

DeliveryDrone::DeliveryDrone(
    string i,
    string n,
    string p,
    int b,
    int s,
    double pr,
    double load,
    string st
)
    : Drone(i, n, p, b, s, pr, st)
{
    payload = load;
}

// ==========================================
// Display Drone Information
// ==========================================

void DeliveryDrone::display() {

    cout << id
        << " | "
        << name
        << " | Delivery | Load: "
        << payload
        << "kg | Battery: "
        << battery
        << "h | Rs."
        << price
        << " | "
        << status
        << endl;
}

// ==========================================
// Drone Type
// ==========================================

string DeliveryDrone::getType() {

    return "Delivery";
}

// ==========================================
// Getter
// ==========================================

double DeliveryDrone::getPayload() const {

    return payload;
}
