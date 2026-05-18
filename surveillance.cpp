#include "SurveillanceDrone.h"

#include <iostream>

using namespace std;

// ==========================================
// Constructor
// ==========================================

SurveillanceDrone::SurveillanceDrone(
    string i,
    string n,
    string p,
    int b,
    int s,
    double pr,
    string cam,
    string st
)
    : Drone(i, n, p, b, s, pr, st)
{
    camera = cam;
}

// ==========================================
// Display Drone Info
// ==========================================

void SurveillanceDrone::display() {

    cout << id << " | "
        << name << " | Surveillance | Cam: "
        << camera << " | Bat: "
        << battery << "h | Rs."
        << price << " | "
        << status << "\n";
}

// ==========================================
// Get Type
// ==========================================

string SurveillanceDrone::getType() {

    return "Surveillance";
}

// ==========================================
// Get Camera
// ==========================================

string SurveillanceDrone::getCamera() const {

    return camera;
}
