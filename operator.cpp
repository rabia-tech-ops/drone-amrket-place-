#include "Operator.h"
#include "ConsoleUI.h"

#include <iostream>

using namespace std;

// ==========================================
// Constructor
// ==========================================

Operator::Operator(string n, string i, FleetManager* f, MissionPlanner* p)
    : Person(n, i, "Operator")
{
    fleet = f;
    planner = p;
}

// ==========================================
// Display Info
// ==========================================

void Operator::displayInfo() {

    cout << CYAN;
    cout << "Operator : " << name
        << " | Role : " << role;
    cout << RESET << endl;
}

// ==========================================
// Operator Panel
// ==========================================

void Operator::showPanel() {

    cout << YELLOW << BOLD;

    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║        OPERATOR CONTROL CENTER       ║\n";
    cout << "╚══════════════════════════════════════╝\n";

    cout << RESET;

    displayInfo();
}

// ==========================================
// Assign Mission
// ==========================================

void Operator::assignMission() {

    planner->assignMission(fleet);
}

// ==========================================
// Monitor Status
// ==========================================

void Operator::monitorStatus() {

    fleet->monitorAll();
}

// ==========================================
// View Delivery Tracking
// ==========================================

void Operator::viewDelivery() {

    planner->trackDelivery();
}
