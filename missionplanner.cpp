#include "MissionPlanner.h"
#include "ConsoleUI.h"

#include <iostream>

using namespace std;

// Constructor
MissionPlanner::MissionPlanner() {

    activeOrder = "ORD102";
    activeDrone = "FoodExpress";
    location = "Rawalpindi";
    destination = "Islamabad";
    progress = 75;
}

// Assign Mission
void MissionPlanner::assignMission(FleetManager* fleet) {

    string id, dest;

    cout << "Enter Drone ID : ";
    cin >> id;

    cout << "Enter Destination : ";
    cin >> dest;

    Drone* d = fleet->findById(id);

    if (d == NULL) {

        cout << RED << "Invalid Drone ID!\n" << RESET;
        return;
    }

    activeDrone = d->getName();
    destination = dest;

    cout << GREEN << "Mission Assigned to " << activeDrone
        << " -> " << destination << "\n" << RESET;
}

// Track Delivery
void MissionPlanner::trackDelivery() {

    cout << CYAN << BOLD;
    cout << "\n====================================\n";
    cout << "       LIVE DELIVERY TRACKING       \n";
    cout << "====================================\n";
    cout << RESET;

    cout << "Order ID : " << activeOrder << endl;
    cout << "Drone    : " << activeDrone << endl;
    cout << "From     : " << location << endl;
    cout << "To       : " << destination << endl;

    cout << "Battery  : 82%\n";
    cout << "Weather  : Clear\n";
    cout << "ETA      : 20 min\n";

    cout << "\nProgress : [";

    for (int i = 0; i < 20; i++) {

        if (i < progress / 5)
            cout << "#";
        else
            cout << ".";
    }

    cout << "] " << progress << "%\n";

    cout << GREEN << "STATUS: PACKAGE IN TRANSIT\n" << RESET;
}

// Emergency Rescue
void MissionPlanner::emergencyRescue() {

    loadingBar("Launching emergency rescue drone...");

    cout << GREEN << "Rescue Mission Dispatched!\n" << RESET;
}

// Weather Check
void MissionPlanner::checkWeather() {

    cout << "Weather: Clear\n";
    cout << "Wind   : Low\n";
    cout << "Safe   : YES\n";
}

// Battery Monitor
void MissionPlanner::checkBattery(FleetManager* fleet) {

    cout << YELLOW << "\n========== BATTERY MONITOR ==========\n" << RESET;

    Drone** d = fleet->getDrones();
    int total = fleet->getDroneCount();

    for (int i = 0; i < total; i++) {

        cout << d[i]->getName()
            << " : "
            << d[i]->getBattery()
            << " hours\n";
    }
}
