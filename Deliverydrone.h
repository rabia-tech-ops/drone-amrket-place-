#ifndef DELIVERYDRONE_H
#define DELIVERYDRONE_H

#include "Drone.h"

using namespace std;

// ==========================================
// Delivery Drone Class
// Derived from Drone
// Used for package delivery
// ==========================================

class DeliveryDrone : public Drone {

private:

    double payload; // Weight capacity in KG

public:

    // Constructor
    DeliveryDrone(
        string i,
        string n,
        string p,
        int b,
        int s,
        double pr,
        double load,
        string st = "Available"
    );

    // Display drone information
    void display();

    // Return drone type
    string getType();

    // Getter
    double getPayload() const;
};

#endif
