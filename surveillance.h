#ifndef SURVEILLANCEDRONE_H
#define SURVEILLANCEDRONE_H

#include "Drone.h"
#include <string>

using namespace std;

// ==========================================
// Surveillance Drone Class
// Used for monitoring and security
// ==========================================

class SurveillanceDrone : public Drone {

private:

    string camera;

public:

    // Constructor
    SurveillanceDrone(
        string i,
        string n,
        string p,
        int b,
        int s,
        double pr,
        string cam,
        string st = "Available"
    );

    // Display drone info
    void display();

    // Drone type
    string getType();

    // Camera info
    string getCamera() const;
};

#endif#pragma once
