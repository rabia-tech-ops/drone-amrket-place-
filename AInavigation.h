#ifndef AINAVIGATION_H
#define AINAVIGATION_H

#include "NavigationSystem.h"

using namespace std;

// ==========================================
// AI Navigation Class
// Derived from NavigationSystem
// Handles smart AI route calculation
// ==========================================

class AINavigation : public NavigationSystem {

public:

    // Constructor
    AINavigation(string src = "", string dest = "");

    // Route calculation function
    void calculateRoute();
};

#endif
