#ifndef MISSIONPLANNER_H
#define MISSIONPLANNER_H

#include "FleetManager.h"
#include <string>

using namespace std;

// ==========================================
// MissionPlanner Class
// Handles missions and delivery tracking
// ==========================================

class MissionPlanner {

private:

    string activeOrder;
    string activeDrone;
    string location;
    string destination;
    int progress;

public:

    // Constructor
    MissionPlanner();

    // Assign mission to drone
    void assignMission(FleetManager* fleet);

    // Track delivery progress
    void trackDelivery();

    // Emergency rescue system
    void emergencyRescue();

    // Weather check
    void checkWeather();

    // Battery monitor
    void checkBattery(FleetManager* fleet);
};

#endif
