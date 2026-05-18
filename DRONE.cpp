#include "Drone.h"

// ==========================================
// Constructor
// ==========================================

Drone::Drone(
    string i,
    string n,
    string p,
    int b,
    int s,
    double pr,
    string st
)
    : id(i),
    name(n),
    purpose(p),
    battery(b),
    speed(s),
    price(pr),
    status(st)
{
}

// ==========================================
// Getters
// ==========================================

string Drone::getId() const {

    return id;
}

string Drone::getName() const {

    return name;
}

string Drone::getPurpose() const {

    return purpose;
}

int Drone::getBattery() const {

    return battery;
}

int Drone::getSpeed() const {

    return speed;
}

double Drone::getPrice() const {

    return price;
}

string Drone::getStatus() const {

    return status;
}

// ==========================================
// Setter
// ==========================================

void Drone::setStatus(string st) {

    status = st;
}
