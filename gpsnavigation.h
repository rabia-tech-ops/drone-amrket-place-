#ifndef GPSNAVIGATION_H
#define GPSNAVIGATION_H

#include "NavigationSystem.h"

using namespace std;

// ==========================================
// GPSNavigation Class
// Derived from NavigationSystem
// Handles GPS route tracking
// ==========================================

class GPSNavigation : public NavigationSystem {

public:

    // Constructor
    GPSNavigation(string src = "", string dest = "");

    // Calculate route
    void calculateRoute();
};

#endif
