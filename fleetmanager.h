#ifndef FLEETMANAGER_H
#define FLEETMANAGER_H

#include "Drone.h"

using namespace std;

// ==========================================
// FleetManager Class
// Manages all drones
// ==========================================

class FleetManager {

private:

    // Drone pointer array
    Drone* drones[100];

    // Total drones
    int totalDrones;

    // One review string per drone slot
    string droneReviews[100];

    // Insurance period string per drone slot (e.g. "2 Years")
    string droneInsurance[100];

    // VIP flag for this session
    bool isVIP;

    // Internal helper : draw the full LIVE DRONE MARKETPLACE table
    void drawTable();

public:

    // Constructor
    FleetManager();

    // Destructor
    ~FleetManager();

    // Load 7 sample drones (3 Rented, 4 Available)
    void loadSampleDrones();

    // Option 1  : show table directly (no sub-menu)
    void showTable();

    // Option 2  : buy drone flow
    void buyDroneMenu();

    // Option 3  : rent drone flow
    void rentDroneMenu();

    // Option 4  : recommend drone by purpose
    void recommendByPurpose();

    // Add new drone (admin)
    void addDroneMenu();

    // Remove drone (admin)
    void removeDroneMenu();

    // Monitor all drones
    void monitorAll();

    // Original recommend (purpose + budget)
    void recommend(string purpose, double budget);

    // Option 10 : search by budget
    void searchByBudget(double maxPrice);

    // Option 7  : reviews — marketplace table + review per drone
    void showReviews();

    // Option 9  : insurance — marketplace table + insurance per drone
    void showInsurance();

    // Option 8  : VIP status menu
    void showVIPMenu();

    // Find drone by ID
    Drone* findById(string id);

    // Get drone list
    Drone** getDrones();

    // Get drone count
    int getDroneCount();
};

#endif
