#ifndef OPERATOR_H
#define OPERATOR_H

#include "Person.h"
#include "FleetManager.h"
#include "MissionPlanner.h"

using namespace std;

// ==========================================
// Operator Class
// Controls drone missions and monitoring
// ==========================================

class Operator : public Person {

private:

    FleetManager* fleet;
    MissionPlanner* planner;

public:

    // Constructor
    Operator(string n, string i, FleetManager* f, MissionPlanner* p);

    // Display operator info
    void displayInfo();

    // Show control panel
    void showPanel();

    // Mission functions
    void assignMission();
    void monitorStatus();
    void viewDelivery();
};

#endif
